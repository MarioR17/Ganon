#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "../include/token.h"

/* Unit Tests for Token Module */

START_TEST(test_token_init_valid)
{
    struct token *tok = token_init("hello", TOKEN_IDENTIFIER);
    
    ck_assert_ptr_nonnull(tok);
    ck_assert_str_eq(tok->value, "hello");
    ck_assert_int_eq(tok->type, TOKEN_IDENTIFIER);
    
    token_free(tok);
}
END_TEST

START_TEST(test_token_init_empty_string)
{
    struct token *tok = token_init("", TOKEN_EOF);
    
    ck_assert_ptr_nonnull(tok);
    ck_assert_str_eq(tok->value, "");
    ck_assert_int_eq(tok->type, TOKEN_EOF);
    
    token_free(tok);
}
END_TEST

START_TEST(test_token_init_long_string)
{
    char long_string[1000];
    memset(long_string, 'a', 999);
    long_string[999] = '\0';
    
    struct token *tok = token_init(long_string, TOKEN_STRING_LITERAL);
    
    ck_assert_ptr_nonnull(tok);
    ck_assert_str_eq(tok->value, long_string);
    ck_assert_int_eq(tok->type, TOKEN_STRING_LITERAL);
    
    token_free(tok);
}
END_TEST

START_TEST(test_token_init_special_chars)
{
    struct token *tok = token_init("hello\nworld\t", TOKEN_STRING_LITERAL);
    
    ck_assert_ptr_nonnull(tok);
    ck_assert_str_eq(tok->value, "hello\nworld\t");
    ck_assert_int_eq(tok->type, TOKEN_STRING_LITERAL);
    
    token_free(tok);
}
END_TEST

START_TEST(test_token_free_null)
{
    /* Should not crash */
    token_free(NULL);
}
END_TEST

START_TEST(test_token_free_valid)
{
    struct token *tok = token_init("test", TOKEN_KEYWORD);
    ck_assert_ptr_nonnull(tok);
    
    /* Should not crash */
    token_free(tok);
}
END_TEST

/* Test memory ownership - ensure value is copied, not just referenced */
START_TEST(test_token_value_independence)
{
    char original[] = "mutable";
    struct token *tok = token_init(original, TOKEN_IDENTIFIER);
    
    /* Modify original string */
    original[0] = 'X';
    
    /* Token should still have original value */
    ck_assert_str_eq(tok->value, "mutable");
    
    token_free(tok);
}
END_TEST

Suite *token_suite(void)
{
    Suite *s;
    TCase *tc_core;
    
    s = suite_create("Token");
    tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_token_init_valid);
    tcase_add_test(tc_core, test_token_init_empty_string);
    tcase_add_test(tc_core, test_token_init_long_string);
    tcase_add_test(tc_core, test_token_init_special_chars);
    tcase_add_test(tc_core, test_token_free_null);
    tcase_add_test(tc_core, test_token_free_valid);
    tcase_add_test(tc_core, test_token_value_independence);
    
    suite_add_tcase(s, tc_core);
    
    return s;
}
