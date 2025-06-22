#include "include/lexer.h"
#include "include/macros.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Lexer* lexerInit(char *src)
{
    Lexer* lex = calloc(1, sizeof(Lexer));
    lex->src = strdup(src);
    lex->src_size = strlen(lex->src);
    lex->cursor_idx = 0;
    lex->cursor = lex->src[lex->cursor_idx];

    return lex;
}

void lexerAdvance(Lexer *lex)
{
    if (lex->cursor != '\0' && (lex->cursor_idx < lex->src_size))
    {
        lex->cursor_idx++;
        lex->cursor = lex->src[lex->cursor_idx];
    } else
    {
        printf("[Lexer] Warning: Did not advance with lexerAdvance call");
    }
}

void lexerSkipWhitespace(Lexer *lex)
{
	while (lex->cursor == 9 || lex->cursor == 10 ||            
	lex->cursor == 11 || lex->cursor == 12 ||
	lex->cursor == 13 || lex->cursor == 32)
	{
	    lexerAdvance(lex);		
	}
}

 char lexerPeek(const Lexer* lex, const unsigned int offset)
{
    return lex->src[MIN((lex->cursor_idx) + offset, lex->src_size)];
}

Token* lexerAdvanceWithToken(Lexer* lex, Token* tok)
{
    return tok;
}

Token* lexerAdvanceWithCurrent(Lexer* lex, TokenType type)
{
    char* value = calloc(2, sizeof(char));
    value[0] = lex->cursor;
    value[1] = '\0';

    Token* tok = tokenInit(value, type);

    lexerAdvance(lex);

    return tok;
}

Token* lexerParseId(Lexer* lex)
{
    char* value = calloc(1, sizeof(char)); 
    unsigned int value_index = 0;

    while (isalnum(lex->cursor) || lex->cursor == '_')
    {
        value = realloc(value, (strlen(value) + 1) * sizeof(char));
        value[value_index] = lex->cursor;
        value_index++;
        lexerAdvance(lex);
    }
    value[value_index] = '\0';

    return tokenInit(value, TOKEN_IDENTIFIER);
}

Token* lexerNextToken(Lexer* lex)
{
    while (lex->cursor != '\0')
    {
        if (isalpha(lex->cursor))
        {
            return lexerAdvanceWithToken(lex, lexerParseId(lex));
        }
    }

    return tokenInit(0, TOKEN_EOF);
}

