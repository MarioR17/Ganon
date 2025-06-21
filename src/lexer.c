#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>

Lexer* initLexer(char *src)
{
    Lexer* lex = calloc(1, sizeof(Lexer));
    lex->src = strdup(src);
    lex->src_size = sizeof(lex->src);
    lex->cursor_idx = 0;
    lex->cursor = lex->src[lex->cursor_idx];

    return lex;
}


