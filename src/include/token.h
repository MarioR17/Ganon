#ifndef GN_TOKEN_H
#define GN_TOKEN_H

typedef struct TOKEN_STRUCT
{
    char* value;
    enum 
    {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN_LBRACKET,
        TOKEN_RBRACKET,
        TOKEN_COLON,
        TOKEN_SEMI,
        TOKEN_COMMA,
        TOKEN_LT,
        TOKEN_GT,
        TOKEN_RIGHT_ARROW,
        TOKEN_INT,
        TOKEN_STRING,
        TOKEN_EOF,
    } type;
} token_G;

token_G* init_token(char* value, int type);
#endif
