#include "include/gn.h"
#include "include/io.h"
#include "include/lexer.h"
#include <stdlib.h>

void gn_compile(char* src)
{
    lexer_G* lexer = init_lexer(src);
    token_G* tok = 0;

    while ((tok = lexer_next_token(lexer))->type != TOKEN_EOF)
    {
        printf("TOK(%s) (%d)\n", tok->value, tok->type);
    }
}

void gn_compile_file(const char* filename)
{
    char* src = gn_read_file(filename);
    gn_compile(src);
    free(src);
}
