#include "parser.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "micro.h"
#include "scanner.h"
#include "semantic.h"

static token lookahead;
static int failed;

static const char *token_name(token value)
{
    static const char *const names[] = {
        "begin", "end", "read", "write", "identifier", "integer literal",
        "'('", "')'", "';'", "','", "':='", "'+'", "'-'", "'|'",
        "end of file"
    };
    return names[value];
}

static void syntax_error(const char *expected)
{
    if (!failed && !scanner_failed()) {
        fprintf(stderr, "%s:%u:%u: syntax error: expected %s, found %s\n",
                scanner_source_name(), scanner_line(), scanner_column(),
                expected, token_name(lookahead));
    }
    failed = 1;
}

static void advance(void)
{
    lookahead = scanner_next();
    if (scanner_failed()) {
        failed = 1;
    }
}

static void match(token expected)
{
    if (failed) {
        return;
    }
    if (lookahead != expected) {
        syntax_error(token_name(expected));
        return;
    }
    advance();
}

static void check_semantics(void)
{
    if (!semantic_ok()) {
        failed = 1;
    }
}

static expr_rec expression(void);

static expr_rec error_expression(void)
{
    expr_rec result = {0};
    result.kind = LITERALEXPR;
    return result;
}

static expr_rec identifier(void)
{
    char saved[MAXIDLEN + 1] = {0};
    expr_rec result;

    if (lookahead != ID) {
        syntax_error("identifier");
        return error_expression();
    }
    (void)strcpy(saved, scanner_lexeme());
    match(ID);
    result = process_id(saved);
    check_semantics();
    return result;
}

static op_rec add_op(void)
{
    token saved;
    op_rec result = {PLUS};

    if (lookahead != PLUSOP && lookahead != MINUSOP) {
        syntax_error("'+' or '-'");
        return result;
    }
    saved = lookahead;
    match(saved);
    result = process_op(saved);
    check_semantics();
    return result;
}

static expr_rec primary(void)
{
    expr_rec first;
    expr_rec second;
    expr_rec third;
    cond_rec context;
    int32_t saved_literal;

    if (failed) {
        return error_expression();
    }
    if (lookahead == ID) {
        return identifier();
    }
    if (lookahead == INTLITERAL) {
        saved_literal = scanner_literal_value();
        match(INTLITERAL);
        first = process_literal(saved_literal);
        check_semantics();
        return first;
    }
    if (lookahead != LPAREN) {
        syntax_error("identifier, integer literal, or '('");
        return error_expression();
    }

    match(LPAREN);
    first = expression();
    if (lookahead != CONDOP) {
        match(RPAREN);
        return first;
    }

    match(CONDOP);
    context = conditional_begin(first);
    check_semantics();
    second = expression();
    match(CONDOP);
    conditional_else(context, second);
    check_semantics();
    third = expression();
    match(RPAREN);
    first = conditional_end(context, third);
    check_semantics();
    return first;
}

static expr_rec expression(void)
{
    expr_rec left = primary();

    while (!failed && (lookahead == PLUSOP || lookahead == MINUSOP)) {
        op_rec operator_record = add_op();
        expr_rec right = primary();
        left = gen_infix(left, operator_record, right);
        check_semantics();
    }
    return left;
}

static void id_list(void)
{
    expr_rec item = identifier();
    read_id(item);
    check_semantics();
    while (!failed && lookahead == COMMA) {
        match(COMMA);
        item = identifier();
        read_id(item);
        check_semantics();
    }
}

static void expr_list(void)
{
    expr_rec item = expression();
    write_expr(item);
    check_semantics();
    while (!failed && lookahead == COMMA) {
        match(COMMA);
        item = expression();
        write_expr(item);
        check_semantics();
    }
}

static void statement(void)
{
    expr_rec target;
    expr_rec value;

    if (lookahead == ID) {
        target = identifier();
        match(ASSIGNOP);
        value = expression();
        assign(target, value);
        check_semantics();
        match(SEMICOLON);
        return;
    }
    if (lookahead == READ) {
        match(READ);
        match(LPAREN);
        id_list();
        match(RPAREN);
        match(SEMICOLON);
        return;
    }
    if (lookahead == WRITE) {
        match(WRITE);
        match(LPAREN);
        expr_list();
        match(RPAREN);
        match(SEMICOLON);
        return;
    }
    syntax_error("statement");
}

static int is_statement_start(token value)
{
    return value == ID || value == READ || value == WRITE;
}

static void statement_list(void)
{
    statement();
    while (!failed && is_statement_start(lookahead)) {
        statement();
    }
}

static void program(void)
{
    if (!semantic_start()) {
        failed = 1;
        return;
    }
    match(BEGIN);
    statement_list();
    match(END);
}

void parser_init(void)
{
    failed = 0;
    advance();
}

int system_goal(void)
{
    program();
    if (!failed && lookahead != SCANEOF) {
        syntax_error("end of file");
    }
    if (!failed && !semantic_finish()) {
        failed = 1;
    }
    return !failed;
}
