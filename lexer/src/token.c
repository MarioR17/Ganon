#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/token.h"

struct token *token_init(const char *value, enum token_type type)
{
        struct token *new_token = malloc(sizeof(struct token));

        if (new_token == NULL) {
                fprintf(stderr, "Could not allocate memory for new token\n");
                exit(EXIT_FAILURE);
        }

        /*
         * Allocate memory for the token value and copy the string.
         *
         * Implemented for portability on even non-POSIX systems.
         */
        size_t value_length = strlen(value);
        char *value_copy = malloc(value_length + 1);

        if (value_copy == NULL) {
                fprintf(stderr, "Could not allocate memory for token value\n");
                free(new_token);
                exit(EXIT_FAILURE);
        }

        memcpy(value_copy, value, value_length);
        value_copy[value_length] = '\0';

        new_token->value = value_copy;
        new_token->type = type;

        return new_token;
}

void token_free(struct token *token)
{
        if (token == NULL) {
                return;
        }

        /* strip away the const qualifier with void since we own the memory */
        free((void*)token->value);
        free(token);
}
