#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>

#include "micro.h"

typedef struct {
    expr_rec result;
    unsigned false_label;
    unsigned end_label;
} cond_rec;

void semantic_init(FILE *output);
int semantic_start(void);
expr_rec process_id(const char *name);
expr_rec process_literal(int32_t value);
op_rec process_op(token operator_token);
expr_rec gen_infix(expr_rec left, op_rec operator_record, expr_rec right);
void assign(expr_rec target, expr_rec source);
void read_id(expr_rec target);
void write_expr(expr_rec expression);
cond_rec conditional_begin(expr_rec condition);
void conditional_else(cond_rec context, expr_rec true_value);
expr_rec conditional_end(cond_rec context, expr_rec false_value);
int semantic_finish(void);
int semantic_ok(void);
void semantic_destroy(void);

#endif
