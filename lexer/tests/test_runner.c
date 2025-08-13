// tests/test_runner.c
#include "../../unity/unity.h"
#include <stdio.h>

// Forward declarations for lexer tests
void test_lexer_init_valid_file(void);
void test_lexer_init_invalid_file(void);
void test_lexer_init_empty_file(void);
void test_lexer_init_single_character_file(void);
void test_lexer_advance_basic(void);
void test_lexer_advance_with_newlines(void);
void test_lexer_advance_to_end_of_input(void);
void test_lexer_advance_past_end_of_input(void);
void test_lexer_advance_multiple_newlines(void);
void test_lexer_free_null(void);
void test_lexer_advance_null(void);
void test_lexer_advance_null_input(void);

// Forward declarations for token tests
void test_token_init_valid_string(void);
void test_token_init_empty_string(void);
void test_token_init_single_character(void);
void test_token_init_long_string(void);
void test_token_init_with_special_characters(void);
void test_token_init_numeric_string(void);
void test_token_init_with_spaces(void);
void test_token_init_zero_type(void);
void test_token_init_negative_type(void);
void test_token_init_large_type_value(void);
void test_token_multiple_create_and_free(void);
void test_token_string_independence(void);
void test_token_free_null(void);
void test_token_free_twice(void);
void test_token_init_very_long_string(void);
void test_token_with_null_characters(void);

// Unity setup and teardown
void setUp(void) {
    // Called before each individual test
    // Can be used for test-specific setup
}

void tearDown(void) {
    // Called after each individual test  
    // Can be used for test-specific cleanup
}

// Test suite runner
int main(void) {
    UNITY_BEGIN();
    
    printf("\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n");
    printf("  LEXER MODULE TESTS\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n\n");
    
    // Lexer initialization tests
    printf("--- Lexer Initialization Tests ---\n");
    RUN_TEST(test_lexer_init_valid_file);
    RUN_TEST(test_lexer_init_invalid_file);
    RUN_TEST(test_lexer_init_empty_file);
    RUN_TEST(test_lexer_init_single_character_file);
    
    // Lexer advance functionality tests
    printf("\n--- Lexer Advance Tests ---\n");
    RUN_TEST(test_lexer_advance_basic);
    RUN_TEST(test_lexer_advance_with_newlines);
    RUN_TEST(test_lexer_advance_to_end_of_input);
    RUN_TEST(test_lexer_advance_past_end_of_input);
    RUN_TEST(test_lexer_advance_multiple_newlines);
    
    // Lexer edge case tests
    printf("\n--- Lexer Edge Case Tests ---\n");
    RUN_TEST(test_lexer_free_null);
    RUN_TEST(test_lexer_advance_null);
    RUN_TEST(test_lexer_advance_null_input);
    
    printf("\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n");
    printf("  TOKEN MODULE TESTS\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n\n");
    
    // Token creation tests
    printf("--- Token Creation Tests ---\n");
    RUN_TEST(test_token_init_valid_string);
    RUN_TEST(test_token_init_empty_string);
    RUN_TEST(test_token_init_single_character);
    RUN_TEST(test_token_init_long_string);
    RUN_TEST(test_token_init_with_special_characters);
    RUN_TEST(test_token_init_numeric_string);
    RUN_TEST(test_token_init_with_spaces);
    
    // Token type tests
    printf("\n--- Token Type Tests ---\n");
    RUN_TEST(test_token_init_zero_type);
    RUN_TEST(test_token_init_negative_type);
    RUN_TEST(test_token_init_large_type_value);
    
    // Token memory management tests
    printf("\n--- Token Memory Management Tests ---\n");
    RUN_TEST(test_token_multiple_create_and_free);
    RUN_TEST(test_token_string_independence);
    
    // Token edge case tests
    printf("\n--- Token Edge Case Tests ---\n");
    RUN_TEST(test_token_free_null);
    RUN_TEST(test_token_free_twice);
    RUN_TEST(test_token_init_very_long_string);
    RUN_TEST(test_token_with_null_characters);
    
    printf("\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n");
    printf("  TEST SUMMARY\n");
    for(int i = 0; i < 50; i++) printf("=");
    printf("\n");
    
    int result = UNITY_END();
    
    if (result == 0) {
        printf("\n✅ All tests passed! Your lexer and token modules are working correctly.\n");
        printf("📊 Run 'make coverage' to see detailed code coverage report.\n");
    } else {
        printf("\n❌ Some tests failed. Check the output above for details.\n");
    }
    
    return result;
}
