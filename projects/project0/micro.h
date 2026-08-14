#ifndef MICRO_H
#define MICRO_H

#include <stdint.h>

#define MAXIDLEN 32

typedef enum {
    BEGIN,
    END,
    READ,
    WRITE,
    ID,
    INTLITERAL,
    LPAREN,
    RPAREN,
    SEMICOLON,
    COMMA,
    ASSIGNOP,
    PLUSOP,
    MINUSOP,
    CONDOP,
    SCANEOF
} token;

typedef enum {
    IDEXPR,
    LITERALEXPR,
    TEMPEXPR
} expr_kind;

typedef enum {
    PLUS,
    MINUS
} op_kind;

typedef struct {
    expr_kind kind;
    char name[MAXIDLEN + 1];
    int32_t value;
    unsigned temp_id;
} expr_rec;

typedef struct {
    op_kind kind;
} op_rec;

#endif
