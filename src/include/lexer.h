#ifndef GN_LEXER_H
#define GN_LEXER_H
#include "token.h"
#include <stdio.h>

typedef struct
{
    char* src;
    size_t src_size;
    char cursor;
    unsigned int cursor_idx;
} Lexer;

Lexer* initLexer(char* src);

#endif // GN_LEXER_H
