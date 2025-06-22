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

Lexer* lexerInit(char* src);

void lexerAdvance(Lexer* lex);

void lexerSkipWhitespace(Lexer* lex);

char lexerPeek(const Lexer* lex, const unsigned int offset);

Token* lexerAdvanceWithToken(Lexer* lex, Token* tok);

Token* lexerAdvanceWithCurrent(Lexer* lex, TokenType type);

Token* lexerNextToken(Lexer* lex);

Token* lexerParseId(Lexer* lex);

#endif // GN_LEXER_H
