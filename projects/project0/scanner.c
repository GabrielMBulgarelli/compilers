#include "scanner.h"

#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static FILE *source;
static const char *source_path;
static int current_char;
static unsigned current_line;
static unsigned current_column;
static unsigned token_line;
static unsigned token_column;
static char lexeme_buffer[MAXIDLEN + 1];
static int32_t literal_value;
static int failed;

static int is_alpha(int c)
{
    return c != EOF && isalpha((unsigned char)c);
}

static int is_digit(int c)
{
    return c != EOF && isdigit((unsigned char)c);
}

static int is_space(int c)
{
    return c != EOF && isspace((unsigned char)c);
}

static void advance_char(void)
{
    if (current_char == '\n') {
        ++current_line;
        current_column = 1;
    } else if (current_char != EOF) {
        ++current_column;
    }
    current_char = fgetc(source);
}

static void lexical_error(const char *message)
{
    if (!failed) {
        fprintf(stderr, "%s:%u:%u: lexical error: %s\n", source_path,
                token_line, token_column, message);
    }
    failed = 1;
}

static token check_reserved(void)
{
    if (strcmp(lexeme_buffer, "begin") == 0) {
        return BEGIN;
    }
    if (strcmp(lexeme_buffer, "end") == 0) {
        return END;
    }
    if (strcmp(lexeme_buffer, "read") == 0) {
        return READ;
    }
    if (strcmp(lexeme_buffer, "write") == 0) {
        return WRITE;
    }
    return ID;
}

static int skip_layout_and_comments(void)
{
    for (;;) {
        while (is_space(current_char)) {
            advance_char();
        }
        if (current_char != '-') {
            return 0;
        }

        token_line = current_line;
        token_column = current_column;
        advance_char();
        if (current_char != '-') {
            return 1;
        }

        while (current_char != '\n' && current_char != EOF) {
            advance_char();
        }
    }
}

void scanner_init(FILE *input, const char *source_name)
{
    source = input;
    source_path = source_name;
    current_line = 1;
    current_column = 1;
    token_line = 1;
    token_column = 1;
    lexeme_buffer[0] = '\0';
    literal_value = 0;
    failed = 0;
    current_char = fgetc(source);
}

token scanner_next(void)
{
    size_t length;
    int too_long;
    int overflow;
    uint32_t value;

    if (failed) {
        return SCANEOF;
    }

    if (skip_layout_and_comments()) {
        return MINUSOP;
    }
    token_line = current_line;
    token_column = current_column;

    if (current_char == EOF) {
        return SCANEOF;
    }

    if (is_alpha(current_char)) {
        length = 0;
        too_long = 0;
        while (is_alpha(current_char) || is_digit(current_char) ||
               current_char == '_') {
            if (length < MAXIDLEN) {
                lexeme_buffer[length++] = (char)current_char;
            } else {
                too_long = 1;
            }
            advance_char();
        }
        lexeme_buffer[length] = '\0';
        if (too_long) {
            lexical_error("identifier exceeds 32 characters");
            return SCANEOF;
        }
        return check_reserved();
    }

    if (is_digit(current_char)) {
        value = 0;
        overflow = 0;
        while (is_digit(current_char)) {
            unsigned digit = (unsigned)(current_char - '0');
            if (value > ((uint32_t)INT32_MAX - digit) / 10U) {
                overflow = 1;
            } else if (!overflow) {
                value = value * 10U + digit;
            }
            advance_char();
        }
        if (overflow) {
            lexical_error("integer literal is outside the int32_t range");
            return SCANEOF;
        }
        literal_value = (int32_t)value;
        return INTLITERAL;
    }

    switch (current_char) {
    case '(':
        advance_char();
        return LPAREN;
    case ')':
        advance_char();
        return RPAREN;
    case ';':
        advance_char();
        return SEMICOLON;
    case ',':
        advance_char();
        return COMMA;
    case '+':
        advance_char();
        return PLUSOP;
    case '|':
        advance_char();
        return CONDOP;
    case ':':
        advance_char();
        if (current_char == '=') {
            advance_char();
            return ASSIGNOP;
        }
        lexical_error("':' must be followed by '='");
        return SCANEOF;
    default:
        lexical_error("invalid character");
        advance_char();
        return SCANEOF;
    }
}

const char *scanner_lexeme(void)
{
    return lexeme_buffer;
}

int32_t scanner_literal_value(void)
{
    return literal_value;
}

const char *scanner_source_name(void)
{
    return source_path;
}

unsigned scanner_line(void)
{
    return token_line;
}

unsigned scanner_column(void)
{
    return token_column;
}

int scanner_failed(void)
{
    return failed;
}
