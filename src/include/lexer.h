#ifndef GN_LEXER_H
#define GN_LEXER_H
#include "token.h"
#include <stdio.h>

typedef struct LEXER_STRUCT
{
    char* src_str;
    size_t src_size;
    char curr_char;
    unsigned int curr_idx;
} lexer_G;

lexer_G* init_lexer(char* src_str);

void lexer_advance(lexer_G* lexer);

void lexer_skip_whitespace(lexer_G* lexer);

token_G* lexer_parse_number(lexer_G* lexer);

token_G* lexer_advance_with(lexer_G* lexer, token_G* token);

token_G* lexer_advance_current(lexer_G* lexer, int type);

char lexer_peek(lexer_G* lexer, int offset);

token_G* lexer_parse_id(lexer_G* lexer);

token_G* lexer_next_token(lexer_G* lexer);

#endif
