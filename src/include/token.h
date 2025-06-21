#ifndef GN_TOKEN_H
#define GN_TOKEN_H

typedef enum
{
    TOKEN_ILLEGAL,
    TOKEN_EOF,
    TOKEN_KEYWORD,

    // Identifiers and literals
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    // operators and punctuation
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_LT,
    TOKEN_GT,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_COLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_ARROW
} TokenType;

typedef struct
{
    char* value;
    TokenType type;
} Token;

Token* initToken(char* value, TokenType type);

#endif //GN_TOKEN_H
