#include "include/lexer.h"
#include "include/token.h"
#include "include/macros.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_G* init_lexer(char* src_str)
{
    lexer_G* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src_str = src_str;
    lexer->src_size = strlen(src_str);
    lexer->curr_idx = 0;
    lexer->curr_char = src_str[lexer->curr_idx];

    return lexer;
}

void lexer_advance(lexer_G* lexer)
{
    if (lexer->curr_idx < lexer->src_size && lexer->curr_char != '\0')
    {
        lexer->curr_idx++;
        lexer->curr_char = lexer->src_str[lexer->curr_idx];
    }
}

void lexer_skip_whitespace(lexer_G* lexer)
{
    while (lexer->curr_char == 9 ||lexer->curr_char == 10 || 
           lexer->curr_char == 11 || lexer->curr_char == 12 ||
           lexer->curr_char == 13 || lexer->curr_char == 32)
    {
        lexer_advance(lexer);
    }
}

char lexer_peek(lexer_G* lexer, int offset)
{
    return lexer->src_str[MIN(lexer->curr_idx + offset, lexer->src_size)];
}

token_G* lexer_advance_with(lexer_G* lexer, token_G* token)
{
    lexer_advance(lexer);
    return token;
}

token_G* lexer_parse_id(lexer_G* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isalnum(lexer->curr_char))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->curr_char, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_ID);
}

token_G* lexer_advance_current(lexer_G* lexer, int type)
{
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->curr_char;
    value[1] = '\0';

    token_G* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

token_G* lexer_parse_number(lexer_G* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isdigit(lexer->curr_char))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){lexer->curr_char, 0});
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_INT);
}

token_G* lexer_next_token(lexer_G* lexer)
{
    while (lexer->curr_char != '\0')
    {
        if (isalpha(lexer->curr_char))
        {
            return lexer_advance_with(lexer, lexer_parse_id(lexer));
        }

        if (isdigit(lexer->curr_char))
        {
            return lexer_advance_with(lexer, lexer_parse_number(lexer));
        }

        switch (lexer->curr_char)
        {
            case '=':
            {
                if (lexer_peek(lexer, 1) == '>')
                {
                    return lexer_advance_with(lexer, init_token("=>", TOKEN_RIGHT_ARROW));
                }
                return lexer_advance_with(lexer, init_token("=", TOKEN_EQUALS));
            } break;
            case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_current(lexer, TOKEN_RBRACE);
            case '[': return lexer_advance_current(lexer, TOKEN_LBRACKET);
            case ']': return lexer_advance_current(lexer, TOKEN_RBRACKET);
            case ':': return lexer_advance_current(lexer, TOKEN_COLON);
            case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
            case '<': return lexer_advance_current(lexer, TOKEN_LT);
            case '>': return lexer_advance_current(lexer, TOKEN_GT);
            case ';': return lexer_advance_current(lexer, TOKEN_SEMI);
            case '\0': break;
            default: printf("[Lexer]: Unexpected character `%c`\n", lexer->curr_char); exit(1); break;
        }
    }

    return init_token(0, TOKEN_EOF);
}

