#ifndef TOKEN_H
#define TOKEN_H

enum token_type {
        TOKEN_ILLEGAL,
        TOKEN_EOF,
        TOKEN_KEYWORD,
        TOKEN_IDENTIFIER,
        TOKEN_INTEGER_LITERAL,
        TOKEN_FLOAT_LITERAL,
        TOKEN_STRING_LITERAL,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_LESS_THAN,
        TOKEN_GREATER_THAN,
        TOKEN_EQUALS,
        TOKEN_NOT_EQUALS,
        TOKEN_SEMI_COLON,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LEFT_PAREN,
        TOKEN_RIGHT_PAREN,
        TOKEN_LEFT_BRACE,
        TOKEN_RIGHT_BRACE,
        TOKEN_LEFT_BRACKET,
        TOKEN_RIGHT_BRACKET,
        TOKEN_DOT,
        TOKEN_ARROW,
};

struct token {
        const char *value;
        enum token_type type;
};

struct token *token_init(const char *value, enum token_type type); 
void token_free(struct token *token);

#endif /* TOKEN_H */
