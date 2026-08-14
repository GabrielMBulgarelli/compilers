#include "semantic.h"

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"
#include "micro.h"

static char (*symbols)[MAXIDLEN + 1];
static size_t symbol_count;
static size_t symbol_capacity;
static unsigned temp_count;
static unsigned label_count;
static int failed;

static expr_rec empty_expression(void)
{
    expr_rec result = {0};
    result.kind = LITERALEXPR;
    return result;
}

static void semantic_error(const char *message)
{
    if (!failed) {
        fprintf(stderr, "semantic error: %s\n", message);
    }
    failed = 1;
}

static void check_codegen(void)
{
    if (!codegen_ok()) {
        semantic_error("could not write generated assembly");
    }
}

static int find_symbol(const char *name)
{
    size_t index;
    for (index = 0; index < symbol_count; ++index) {
        if (strcmp(symbols[index], name) == 0) {
            return 1;
        }
    }
    return 0;
}

static int add_symbol(const char *name)
{
    char (*replacement)[MAXIDLEN + 1];
    size_t new_capacity;

    if (find_symbol(name)) {
        return 1;
    }
    if (symbol_count == symbol_capacity) {
        new_capacity = symbol_capacity == 0 ? 16 : symbol_capacity * 2;
        if (new_capacity < symbol_capacity ||
            new_capacity > SIZE_MAX / sizeof *symbols) {
            semantic_error("too many identifiers");
            return 0;
        }
        replacement = realloc(symbols, new_capacity * sizeof *symbols);
        if (replacement == NULL) {
            semantic_error("out of memory while recording identifiers");
            return 0;
        }
        symbols = replacement;
        symbol_capacity = new_capacity;
    }
    (void)strcpy(symbols[symbol_count], name);
    ++symbol_count;
    return 1;
}

static unsigned new_temp(void)
{
    if (temp_count == UINT_MAX) {
        semantic_error("too many compiler temporaries");
        return 0;
    }
    return ++temp_count;
}

static unsigned new_label(void)
{
    if (label_count == UINT_MAX) {
        semantic_error("too many conditional labels");
        return 0;
    }
    return ++label_count;
}

void semantic_init(FILE *output)
{
    symbols = NULL;
    symbol_count = 0;
    symbol_capacity = 0;
    temp_count = 0;
    label_count = 0;
    failed = 0;
    codegen_init(output);
}

int semantic_start(void)
{
    codegen_start();
    check_codegen();
    return !failed;
}

expr_rec process_id(const char *name)
{
    expr_rec result = empty_expression();
    if (failed || !add_symbol(name)) {
        return result;
    }
    result.kind = IDEXPR;
    (void)strcpy(result.name, name);
    return result;
}

expr_rec process_literal(int32_t value)
{
    expr_rec result = empty_expression();
    result.kind = LITERALEXPR;
    result.value = value;
    return result;
}

op_rec process_op(token operator_token)
{
    op_rec result;
    if (operator_token == PLUSOP) {
        result.kind = PLUS;
    } else if (operator_token == MINUSOP) {
        result.kind = MINUS;
    } else {
        result.kind = PLUS;
        semantic_error("invalid arithmetic operator");
    }
    return result;
}

expr_rec gen_infix(expr_rec left, op_rec operator_record, expr_rec right)
{
    expr_rec result = empty_expression();

    if (failed) {
        return result;
    }
    if (left.kind == LITERALEXPR && right.kind == LITERALEXPR) {
        int64_t folded = operator_record.kind == PLUS
                             ? (int64_t)left.value + (int64_t)right.value
                             : (int64_t)left.value - (int64_t)right.value;
        if (folded < INT32_MIN || folded > INT32_MAX) {
            semantic_error("constant expression is outside the int32_t range");
            return result;
        }
        result.kind = LITERALEXPR;
        result.value = (int32_t)folded;
        return result;
    }

    result.kind = TEMPEXPR;
    result.temp_id = new_temp();
    if (failed) {
        return empty_expression();
    }
    codegen_binary(left, operator_record, right, result.temp_id);
    check_codegen();
    return result;
}

void assign(expr_rec target, expr_rec source)
{
    if (failed) {
        return;
    }
    if (target.kind != IDEXPR) {
        semantic_error("assignment target is not an identifier");
        return;
    }
    codegen_assign(target.name, source);
    check_codegen();
}

void read_id(expr_rec target)
{
    if (failed) {
        return;
    }
    if (target.kind != IDEXPR) {
        semantic_error("read target is not an identifier");
        return;
    }
    codegen_read(target.name);
    check_codegen();
}

void write_expr(expr_rec expression_record)
{
    if (failed) {
        return;
    }
    codegen_write(expression_record);
    check_codegen();
}

cond_rec conditional_begin(expr_rec condition)
{
    cond_rec context;
    context.result = empty_expression();
    context.result.kind = TEMPEXPR;
    context.result.temp_id = new_temp();
    context.false_label = new_label();
    context.end_label = new_label();
    if (!failed) {
        codegen_conditional_begin(condition, context.false_label);
        check_codegen();
    }
    return context;
}

void conditional_else(cond_rec context, expr_rec true_value)
{
    if (failed) {
        return;
    }
    codegen_conditional_else(context.result.temp_id, true_value,
                             context.false_label, context.end_label);
    check_codegen();
}

expr_rec conditional_end(cond_rec context, expr_rec false_value)
{
    if (!failed) {
        codegen_conditional_end(context.result.temp_id, false_value,
                                context.end_label);
        check_codegen();
    }
    return context.result;
}

int semantic_finish(void)
{
    if (failed) {
        return 0;
    }
    codegen_finish(symbols, symbol_count, temp_count);
    check_codegen();
    return !failed;
}

int semantic_ok(void)
{
    return !failed;
}

void semantic_destroy(void)
{
    free(symbols);
    symbols = NULL;
    symbol_count = 0;
    symbol_capacity = 0;
}
