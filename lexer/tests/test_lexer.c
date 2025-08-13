#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/lexer.h"

/* Helper function to create temporary test files */
static char *create_temp_file(const char *content)
{
    static char template[] = "/tmp/lexer_test_XXXXXX";
    char *filename = malloc(sizeof(template));
    strcpy(filename, template);
    
    int fd = mkstemp(filename);
    if (fd == -1) {
        free(filename);
        return NULL;
    }
    
    write(fd, content, strlen(content));
    close(fd);
    
    return filename;
}

/* Unit Tests for Lexer Module */

START_TEST(test_lexer_init_valid_file)
{
    char *filename = create_temp_file("int main() { return 0; }");
    ck_assert_ptr_nonnull(filename);
    
    struct lexer *lex = lexer_init(filename);
    
    ck_assert_ptr_nonnull(lex);
    ck_assert_ptr_nonnull(lex->input);
    ck_assert_str_eq(lex->input, "int main() { return 0; }");
    ck_assert_int_eq(lex->pos, 0);
    ck_assert_int_eq(lex->cursor, 'i');
    ck_assert_int_eq(lex->line, 1);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_free(lex);
    unlink(filename);
    free(filename);
}
END_TEST

START_TEST(test_lexer_init_empty_file)
{
    char *filename = create_temp_file("");
    ck_assert_ptr_nonnull(filename);
    
    struct lexer *lex = lexer_init(filename);
    
    ck_assert_ptr_nonnull(lex);
    ck_assert_ptr_nonnull(lex->input);
    ck_assert_str_eq(lex->input, "");
    ck_assert_int_eq(lex->pos, 0);
    ck_assert_int_eq(lex->cursor, '\0');
    ck_assert_int_eq(lex->line, 1);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_free(lex);
    unlink(filename);
    free(filename);
}
END_TEST

START_TEST(test_lexer_init_nonexistent_file)
{
    struct lexer *lex = lexer_init("/nonexistent/file.txt");
    ck_assert_ptr_null(lex);
}
END_TEST

START_TEST(test_lexer_advance_basic)
{
    char *filename = create_temp_file("abc");
    struct lexer *lex = lexer_init(filename);
    
    ck_assert_int_eq(lex->cursor, 'a');
    ck_assert_int_eq(lex->pos, 0);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_advance(lex);
    ck_assert_int_eq(lex->cursor, 'b');
    ck_assert_int_eq(lex->pos, 1);
    ck_assert_int_eq(lex->col, 2);
    
    lexer_advance(lex);
    ck_assert_int_eq(lex->cursor, 'c');
    ck_assert_int_eq(lex->pos, 2);
    ck_assert_int_eq(lex->col, 3);
    
    lexer_advance(lex);
    ck_assert_int_eq(lex->cursor, '\0');
    ck_assert_int_eq(lex->pos, 3);
    ck_assert_int_eq(lex->col, 4);
    
    lexer_free(lex);
    unlink(filename);
    free(filename);
}
END_TEST

START_TEST(test_lexer_advance_newlines)
{
    char *filename = create_temp_file("a\nb\nc");
    struct lexer *lex = lexer_init(filename);
    
    ck_assert_int_eq(lex->cursor, 'a');
    ck_assert_int_eq(lex->line, 1);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_advance(lex); /* move to \n */
    ck_assert_int_eq(lex->cursor, '\n');
    ck_assert_int_eq(lex->line, 1);
    ck_assert_int_eq(lex->col, 2);
    
    lexer_advance(lex); /* move to 'b', line should increment */
    ck_assert_int_eq(lex->cursor, 'b');
    ck_assert_int_eq(lex->line, 2);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_advance(lex); /* move to \n */
    lexer_advance(lex); /* move to 'c' */
    ck_assert_int_eq(lex->cursor, 'c');
    ck_assert_int_eq(lex->line, 3);
    ck_assert_int_eq(lex->col, 1);
    
    lexer_free(lex);
    unlink(filename);
    free(filename);
}
END_TEST

START_TEST(test_lexer_advance_past_end)
{
    char *filename = create_temp_file("a");
    struct lexer *lex = lexer_init(filename);
    
    lexer_advance(lex); /* move to '\0' */
    ck_assert_int_eq(lex->cursor, '\0');
    
    /* Advancing past end should not crash but should print error */
    lexer_advance(lex);
    ck_assert_int_eq(lex->cursor, '\0');
    
    lexer_free(lex);
    unlink(filename);
    free(filename);
}
END_TEST

START_TEST(test_lexer_advance_null_lexer)
{
    /* Should not crash */
    lexer_advance(NULL);
}
END_TEST

START_TEST(test_lexer_free_null)
{
    /* Should not crash */
    lexer_free(NULL);
}
END_TEST

START_TEST(test_lexer_free_valid)
{
    char *filename = create_temp_file("test");
    struct lexer *lex = lexer_init(filename);
    ck_assert_ptr_nonnull(lex);
    
    /* Should not crash */
    lexer_free(lex);
    
    unlink(filename);
    free(filename);
}
END_TEST

Suite *lexer_suite(void)
{
    Suite *s;
    TCase *tc_core, *tc_edge;
    
    s = suite_create("Lexer");
    
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_lexer_init_valid_file);
    tcase_add_test(tc_core, test_lexer_init_empty_file);
    tcase_add_test(tc_core, test_lexer_advance_basic);
    tcase_add_test(tc_core, test_lexer_advance_newlines);
    tcase_add_test(tc_core, test_lexer_free_valid);
    
    tc_edge = tcase_create("EdgeCases");
    tcase_add_test(tc_edge, test_lexer_init_nonexistent_file);
    tcase_add_test(tc_edge, test_lexer_advance_past_end);
    tcase_add_test(tc_edge, test_lexer_advance_null_lexer);
    tcase_add_test(tc_edge, test_lexer_free_null);
    
    suite_add_tcase(s, tc_core);
    suite_add_tcase(s, tc_edge);
    
    return s;
}
