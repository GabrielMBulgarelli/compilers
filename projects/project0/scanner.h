#ifndef SCANNER_H
#define SCANNER_H

#include <stdint.h>
#include <stdio.h>

#include "micro.h"

void scanner_init(FILE *input, const char *source_name);
token scanner_next(void);
const char *scanner_lexeme(void);
int32_t scanner_literal_value(void);
const char *scanner_source_name(void);
unsigned scanner_line(void);
unsigned scanner_column(void);
int scanner_failed(void);

#endif
