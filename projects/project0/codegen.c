#include "codegen.h"

#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "micro.h"

static FILE *assembly;
static int failed;

static void emit(const char *format, ...)
{
    va_list arguments;
    int result;

    if (failed) {
        return;
    }
    va_start(arguments, format);
    result = vfprintf(assembly, format, arguments);
    va_end(arguments);
    if (result < 0) {
        failed = 1;
    }
}

static void emit_variable(const char *name)
{
    emit("micro_var_%s", name);
}

static void emit_temporary(unsigned identifier)
{
    emit("micro_tmp_%u", identifier);
}

static void load_expression(expr_rec expression, const char *reg)
{
    switch (expression.kind) {
    case IDEXPR:
        emit("\tmovl ");
        emit_variable(expression.name);
        emit("(%%rip), %s\n", reg);
        break;
    case LITERALEXPR:
        emit("\tmovl $%" PRId32 ", %s\n", expression.value, reg);
        break;
    case TEMPEXPR:
        emit("\tmovl ");
        emit_temporary(expression.temp_id);
        emit("(%%rip), %s\n", reg);
        break;
    }
}

static void emit_memory_operand(expr_rec expression)
{
    if (expression.kind == IDEXPR) {
        emit_variable(expression.name);
    } else {
        emit_temporary(expression.temp_id);
    }
    emit("(%%rip)");
}

static void store_temporary(unsigned target, expr_rec source)
{
    load_expression(source, "%eax");
    emit("\tmovl %%eax, ");
    emit_temporary(target);
    emit("(%%rip)\n");
}

void codegen_init(FILE *output)
{
    assembly = output;
    failed = 0;
}

void codegen_start(void)
{
    emit(".section .rodata\n");
    emit(".Lmicro_read_format:\n\t.string \"%%d\"\n");
    emit(".Lmicro_write_format:\n\t.string \"%%d\\n\"\n");
    emit(".text\n.globl main\n.type main, @function\nmain:\n");
    emit("\tpushq %%rbp\n\tmovq %%rsp, %%rbp\n");
}

void codegen_binary(expr_rec left, op_rec operator_record, expr_rec right,
                    unsigned result_temp)
{
    load_expression(left, "%eax");
    emit(operator_record.kind == PLUS ? "\taddl " : "\tsubl ");
    if (right.kind == LITERALEXPR) {
        emit("$%" PRId32, right.value);
    } else {
        emit_memory_operand(right);
    }
    emit(", %%eax\n\tmovl %%eax, ");
    emit_temporary(result_temp);
    emit("(%%rip)\n");
}

void codegen_assign(const char *target, expr_rec source)
{
    load_expression(source, "%eax");
    emit("\tmovl %%eax, ");
    emit_variable(target);
    emit("(%%rip)\n");
}

void codegen_read(const char *target)
{
    emit("\tleaq ");
    emit_variable(target);
    emit("(%%rip), %%rsi\n");
    emit("\tleaq .Lmicro_read_format(%%rip), %%rdi\n");
    emit("\txorl %%eax, %%eax\n\tcall scanf@PLT\n");
}

void codegen_write(expr_rec expression)
{
    load_expression(expression, "%esi");
    emit("\tleaq .Lmicro_write_format(%%rip), %%rdi\n");
    emit("\txorl %%eax, %%eax\n\tcall printf@PLT\n");
}

void codegen_conditional_begin(expr_rec condition, unsigned false_label)
{
    load_expression(condition, "%eax");
    emit("\tcmpl $0, %%eax\n\tje .Lmicro_false_%u\n", false_label);
}

void codegen_conditional_else(unsigned result_temp, expr_rec true_value,
                              unsigned false_label, unsigned end_label)
{
    store_temporary(result_temp, true_value);
    emit("\tjmp .Lmicro_end_%u\n", end_label);
    emit(".Lmicro_false_%u:\n", false_label);
}

void codegen_conditional_end(unsigned result_temp, expr_rec false_value,
                             unsigned end_label)
{
    store_temporary(result_temp, false_value);
    emit(".Lmicro_end_%u:\n", end_label);
}

void codegen_finish(char (*symbol_names)[MAXIDLEN + 1],
                    size_t symbol_count, unsigned temp_count)
{
    size_t index;
    unsigned temp;

    emit("\tmovl $0, %%eax\n\tleave\n\tret\n");
    emit(".size main, .-main\n.bss\n.align 4\n");
    for (index = 0; index < symbol_count; ++index) {
        emit_variable(symbol_names[index]);
        emit(":\n\t.zero 4\n");
    }
    for (temp = 1; temp <= temp_count; ++temp) {
        emit_temporary(temp);
        emit(":\n\t.zero 4\n");
    }
    emit(".section .note.GNU-stack,\"\",@progbits\n");
}

int codegen_ok(void)
{
    return !failed && !ferror(assembly);
}
