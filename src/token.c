#include "./include/token.h"
#include <stdlib.h>
#include <string.h>

Token* initToken(char* value, TokenType type)
{
    Token* tok = calloc(1, sizeof(Token));
    tok->value = strdup(value);
    tok->type = type;

    return tok;
}

