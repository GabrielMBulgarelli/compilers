#ifndef CODEGEN_H
#define CODEGEN_H

#include <stddef.h>
#include <stdio.h>

#include "micro.h"

void codegen_init(FILE *output);
void codegen_start(void);
void codegen_binary(expr_rec left, op_rec operator_record, expr_rec right,
                    unsigned result_temp);
void codegen_assign(const char *target, expr_rec source);
void codegen_read(const char *target);
void codegen_write(expr_rec expression);
void codegen_conditional_begin(expr_rec condition, unsigned false_label);
void codegen_conditional_else(unsigned result_temp, expr_rec true_value,
                              unsigned false_label, unsigned end_label);
void codegen_conditional_end(unsigned result_temp, expr_rec false_value,
                             unsigned end_label);
void codegen_finish(char (*symbols)[MAXIDLEN + 1], size_t symbol_count,
                    unsigned temp_count);
int codegen_ok(void);

#endif
