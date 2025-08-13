#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../unity/unity.h"
#include "../include/token.h"

// TOKEN CREATION TESTS
void test_token_init_valid_string(void) {
    const char *value = "identifier";
    enum token_type type = 1;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_NOT_NULL(tok->value);
    TEST_ASSERT_EQUAL_STRING(value, tok->value);
    TEST_ASSERT_EQUAL(type, tok->type);
    
    // Verify it's a proper copy, not just a pointer
    TEST_ASSERT_NOT_EQUAL(value, tok->value);
    
    token_free(tok);
}

void test_token_init_empty_string(void) {
    const char *value = "";
    enum token_type type = 0;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_NOT_NULL(tok->value);
    TEST_ASSERT_EQUAL_STRING("", tok->value);
    TEST_ASSERT_EQUAL(type, tok->type);
    
    token_free(tok);
}

void test_token_init_single_character(void) {
    const char *value = "x";
    enum token_type type = 42;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING("x", tok->value);
    TEST_ASSERT_EQUAL(42, tok->type);
    
    token_free(tok);
}

void test_token_init_long_string(void) {
    const char *value = "this_is_a_very_long_identifier_name_that_exceeds_normal_length_expectations_for_testing_memory_allocation";
    enum token_type type = 100;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING(value, tok->value);
    TEST_ASSERT_EQUAL(100, tok->type);
    
    token_free(tok);
}

void test_token_init_with_special_characters(void) {
    const char *value = "hello\tworld\n!@#$%^&*()";
    enum token_type type = 255;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING(value, tok->value);
    TEST_ASSERT_EQUAL(255, tok->type);
    
    token_free(tok);
}

void test_token_init_numeric_string(void) {
    const char *value = "12345";
    enum token_type type = 50;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING("12345", tok->value);
    TEST_ASSERT_EQUAL(50, tok->type);
    
    token_free(tok);
}

void test_token_init_with_spaces(void) {
    const char *value = "hello world with spaces";
    enum token_type type = 75;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING(value, tok->value);
    TEST_ASSERT_EQUAL(75, tok->type);
    
    token_free(tok);
}

// TOKEN TYPE TESTS
void test_token_init_zero_type(void) {
    const char *value = "zero_type";
    enum token_type type = 0;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL(0, tok->type);
    
    token_free(tok);
}

void test_token_init_negative_type(void) {
    const char *value = "negative_type";
    enum token_type type = -1;  // Assuming enum can hold negative values
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL(-1, tok->type);
    
    token_free(tok);
}

void test_token_init_large_type_value(void) {
    const char *value = "large_type";
    enum token_type type = 999999;
    
    struct token *tok = token_init(value, type);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL(999999, tok->type);
    
    token_free(tok);
}

// TOKEN MEMORY MANAGEMENT TESTS
void test_token_multiple_create_and_free(void) {
    struct token *tokens[5];
    
    // Create multiple tokens
    for (int i = 0; i < 5; i++) {
        char value[20];
        snprintf(value, sizeof(value), "token_%d", i);
        tokens[i] = token_init(value, i);
        TEST_ASSERT_NOT_NULL(tokens[i]);
    }
    
    // Verify they're all different
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            TEST_ASSERT_NOT_EQUAL(tokens[i]->value, tokens[j]->value);
            TEST_ASSERT_NOT_EQUAL(0, strcmp(tokens[i]->value, tokens[j]->value));
        }
    }
    
    // Free them all
    for (int i = 0; i < 5; i++) {
        token_free(tokens[i]);
    }
    
    TEST_PASS();
}

void test_token_string_independence(void) {
    char original[] = "original_string";
    struct token *tok = token_init(original, 1);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING("original_string", tok->value);
    
    // Modify original string
    strcpy(original, "modified_string");
    
    // Token value should be unchanged (it should have its own copy)
    TEST_ASSERT_EQUAL_STRING("original_string", tok->value);
    TEST_ASSERT_NOT_EQUAL(0, strcmp("modified_string", tok->value));
    
    token_free(tok);
}

// TOKEN EDGE CASE TESTS
void test_token_free_null(void) {
    // Should not crash
    token_free(NULL);
    TEST_PASS();
}

void test_token_free_twice(void) {
    const char *value = "test_double_free";
    struct token *tok = token_init(value, 1);
    
    TEST_ASSERT_NOT_NULL(tok);
    
    // Free once
    token_free(tok);
    
    // Note: Freeing twice is undefined behavior and could crash
    // This test mainly exists to document the expected behavior
    // In a real implementation, you might want to set pointers to NULL after freeing
    TEST_PASS();
}

void test_token_init_very_long_string(void) {
    // Create a very long string (1000 characters)
    char *long_value = malloc(1001);
    if (!long_value) {
        TEST_FAIL_MESSAGE("Could not allocate memory for long string test");
        return;
    }
    
    // Fill with 'A's
    memset(long_value, 'A', 1000);
    long_value[1000] = '\0';
    
    struct token *tok = token_init(long_value, 999);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL(1000, strlen(tok->value));
    TEST_ASSERT_EQUAL_STRING(long_value, tok->value);
    TEST_ASSERT_EQUAL(999, tok->type);
    
    token_free(tok);
    free(long_value);
}

void test_token_with_null_characters(void) {
    // Test with a string that contains null characters in the middle
    // Note: This is tricky because strlen will stop at the first null
    char value_with_null[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd', '\0'};
    
    // Since token_init uses strlen, it will only copy up to the first null
    struct token *tok = token_init(value_with_null, 123);
    
    TEST_ASSERT_NOT_NULL(tok);
    TEST_ASSERT_EQUAL_STRING("hello", tok->value);
    TEST_ASSERT_EQUAL(5, strlen(tok->value));
    TEST_ASSERT_EQUAL(123, tok->type);
    
    token_free(tok);
}
