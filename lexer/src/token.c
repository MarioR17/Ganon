#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/token.h"

struct token *token_init(const char *value, enum token_type type)
{
        struct token *new_token;
        size_t value_length;
        char *value_copy;

        new_token = malloc(sizeof(struct token));

        if (new_token == NULL) {
                fprintf(stderr,
                        "token: new token allocation failed `%d`\n", type);
                goto out;
        }

        /*
         * Allocate memory for the token value and copy the string.
         *
         * Implemented for portability on even non-POSIX systems.
         */
        value_length = strlen(value);
        value_copy = malloc(value_length + 1);

        if (value_copy == NULL) {
                fprintf(stderr, 
                        "token: new token value allocation failed `%s`\n", 
                        value);
                goto out_free;
        }

        memcpy(value_copy, value, value_length);
        value_copy[value_length] = '\0';

        new_token->value = value_copy;
        new_token->type = type;

        return new_token;

out_free:
        free(new_token);
out:
        return NULL;
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
