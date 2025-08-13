#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#include "token.h"

struct lexer {
        char *input;
        size_t pos;
        char cursor;
        size_t line;
        size_t col;
};

struct lexer *lexer_init(const char *filename);
void lexer_free(struct lexer *lexer);
void lexer_advance(struct lexer *lexer);

#endif /* LEXER_H */
