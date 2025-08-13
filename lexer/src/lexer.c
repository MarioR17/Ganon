#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"

struct lexer *lexer_init(const char *filename)
{
        FILE *fp;
        struct lexer *lexer;
        unsigned long length;

        fp = fopen(filename, "rb");

        if (!fp) {
                fprintf(stderr, "lexer: could not open file `%s`\n", 
                        filename);
                goto out;
        }

        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (length < 0) {
                fprintf(stderr,
                        "lexer: could not determine file size of `%s`\n", 
                        filename);
                goto out_close_file;
        }

        lexer = malloc(sizeof(struct lexer));

        if (!lexer) {
                fprintf(stderr, "lexer: new lexer allocation failed\n");
                goto out_close_file;
        }

        lexer->input = malloc(length + 1);

        if (!lexer->input) {
                fprintf(stderr, "lexer: allocation of file input failed\n");
                goto out_free_lexer;
        }

        if (fread(lexer->input, 1, length, fp) != length) {
                fprintf(stderr, "lexer: reading file `%s` failed\n", filename);
                goto out_free_input;
        }
        lexer->input[length] = '\0';

        lexer->pos = 0;
        lexer->cursor = lexer->input[lexer->pos];
        lexer->line = 1;
        lexer->col = 1;

        fclose(fp);

        return lexer;

out_free_input:
        free((void*)lexer->input);
out_free_lexer:
        free(lexer);
out_close_file:
        fclose(fp);
out:
        return NULL;
}

void lexer_free(struct lexer *lexer)
{
        if (!lexer)
                return;

        free((void*)lexer->input);
        free(lexer);
}

void lexer_advance(struct lexer *lexer)
{
        if (!lexer || !lexer->input)
                return;

        if (lexer->cursor == '\0') {
                fprintf(stderr, "lexer: reached end of input\n");
                return;
        }

        if (lexer->cursor == '\n') {
                lexer->line++;
                lexer->col = 1;
        } else {
                lexer->col++;
        }

        lexer->pos++;
        lexer->cursor = lexer->input[lexer->pos];
}
