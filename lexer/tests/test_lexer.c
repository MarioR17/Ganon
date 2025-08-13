#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../../unity/unity.h"
#include "../include/lexer.h"

// Test helper functions for lexer tests
static void create_test_file(const char *filename, const char *content) {
    char filepath[256];
    const char *temp_dir = getenv("TEST_TEMP_DIR");
    if (temp_dir) {
        snprintf(filepath, sizeof(filepath), "%s/%s", temp_dir, filename);
    } else {
        snprintf(filepath, sizeof(filepath), "%s", filename);
    }
    
    FILE *fp = fopen(filepath, "w");
    if (fp) {
        fprintf(fp, "%s", content);
        fclose(fp);
    }
}

static void cleanup_test_file(const char *filename) {
    char filepath[256];
    const char *temp_dir = getenv("TEST_TEMP_DIR");
    if (temp_dir) {
        snprintf(filepath, sizeof(filepath), "%s/%s", temp_dir, filename);
    } else {
        snprintf(filepath, sizeof(filepath), "%s", filename);
    }
    remove(filepath);
}

static const char* get_test_filepath(const char *filename) {
    static char filepath[256];
    const char *temp_dir = getenv("TEST_TEMP_DIR");
    if (temp_dir) {
        snprintf(filepath, sizeof(filepath), "%s/%s", temp_dir, filename);
    } else {
        snprintf(filepath, sizeof(filepath), "%s", filename);
    }
    return filepath;
}

// LEXER INITIALIZATION TESTS
void test_lexer_init_valid_file(void) {
    const char *filename = "test_valid.txt";
    const char *content = "hello world";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(get_test_filepath(filename));
    
    TEST_ASSERT_NOT_NULL(lex);
    TEST_ASSERT_NOT_NULL(lex->input);
    TEST_ASSERT_EQUAL_STRING(content, lex->input);
    TEST_ASSERT_EQUAL('h', lex->cursor);
    TEST_ASSERT_EQUAL(0, lex->pos);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_init_invalid_file(void) {
    struct lexer *lex = lexer_init("nonexistent_file_12345.txt");
    TEST_ASSERT_NULL(lex);
}

void test_lexer_init_empty_file(void) {
    const char *filename = "test_empty.txt";
    
    create_test_file(filename, "");
    
    struct lexer *lex = lexer_init(get_test_filepath(filename));
    
    TEST_ASSERT_NOT_NULL(lex);
    TEST_ASSERT_EQUAL('\0', lex->cursor);
    TEST_ASSERT_EQUAL(0, lex->pos);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_init_single_character_file(void) {
    const char *filename = "test_single.txt";
    const char *content = "x";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    TEST_ASSERT_NOT_NULL(lex);
    TEST_ASSERT_EQUAL('x', lex->cursor);
    TEST_ASSERT_EQUAL(0, lex->pos);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

// LEXER ADVANCE TESTS
void test_lexer_advance_basic(void) {
    const char *filename = "test_advance_basic.txt";
    const char *content = "abc";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    // Initial state: 'a'
    TEST_ASSERT_EQUAL('a', lex->cursor);
    TEST_ASSERT_EQUAL(0, lex->pos);
    TEST_ASSERT_EQUAL(1, lex->col);
    TEST_ASSERT_EQUAL(1, lex->line);
    
    // Advance to 'b'
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('b', lex->cursor);
    TEST_ASSERT_EQUAL(1, lex->pos);
    TEST_ASSERT_EQUAL(2, lex->col);
    TEST_ASSERT_EQUAL(1, lex->line);
    
    // Advance to 'c'
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('c', lex->cursor);
    TEST_ASSERT_EQUAL(2, lex->pos);
    TEST_ASSERT_EQUAL(3, lex->col);
    TEST_ASSERT_EQUAL(1, lex->line);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_advance_with_newlines(void) {
    const char *filename = "test_advance_newlines.txt";
    const char *content = "line1\nline2\nline3";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    // Start: 'l' at line 1, col 1
    TEST_ASSERT_EQUAL('l', lex->cursor);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    // Advance through "line1"
    for (int i = 0; i < 4; i++) {
        lexer_advance(lex);
    }
    TEST_ASSERT_EQUAL('1', lex->cursor);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(5, lex->col);
    
    // Advance to '\n'
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\n', lex->cursor);
    TEST_ASSERT_EQUAL(1, lex->line);
    TEST_ASSERT_EQUAL(6, lex->col);
    
    // Advance past newline - should increment line, reset col
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('l', lex->cursor);
    TEST_ASSERT_EQUAL(2, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_advance_to_end_of_input(void) {
    const char *filename = "test_advance_end.txt";
    const char *content = "xy";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    // Advance to 'y'
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('y', lex->cursor);
    
    // Advance to end
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\0', lex->cursor);
    
    // Position should be at end
    TEST_ASSERT_EQUAL(2, lex->pos);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_advance_past_end_of_input(void) {
    const char *filename = "test_advance_past_end.txt";
    const char *content = "z";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    // Advance to end
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\0', lex->cursor);
    
    // Try to advance past end - should not change position
    size_t old_pos = lex->pos;
    size_t old_line = lex->line;
    size_t old_col = lex->col;
    
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\0', lex->cursor);
    TEST_ASSERT_EQUAL(old_pos, lex->pos);
    TEST_ASSERT_EQUAL(old_line, lex->line);
    TEST_ASSERT_EQUAL(old_col, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

void test_lexer_advance_multiple_newlines(void) {
    const char *filename = "test_multiple_newlines.txt";
    const char *content = "a\n\n\nb";
    
    create_test_file(filename, content);
    
    struct lexer *lex = lexer_init(filename);
    
    // Start at 'a'
    TEST_ASSERT_EQUAL('a', lex->cursor);
    TEST_ASSERT_EQUAL(1, lex->line);
    
    // First newline
    lexer_advance(lex);
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\n', lex->cursor);
    TEST_ASSERT_EQUAL(2, lex->line);
    
    // Second newline
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\n', lex->cursor);
    TEST_ASSERT_EQUAL(3, lex->line);
    
    // Third newline
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('\n', lex->cursor);
    TEST_ASSERT_EQUAL(4, lex->line);
    
    // Finally 'b'
    lexer_advance(lex);
    TEST_ASSERT_EQUAL('b', lex->cursor);
    TEST_ASSERT_EQUAL(5, lex->line);
    TEST_ASSERT_EQUAL(1, lex->col);
    
    lexer_free(lex);
    cleanup_test_file(filename);
}

// LEXER EDGE CASE TESTS
void test_lexer_free_null(void) {
    // Should not crash
    lexer_free(NULL);
    TEST_PASS();
}

void test_lexer_advance_null(void) {
    // Should not crash
    lexer_advance(NULL);
    TEST_PASS();
}

void test_lexer_advance_null_input(void) {
    // Create a lexer manually with NULL input to test robustness
    struct lexer *lex = malloc(sizeof(struct lexer));
    if (lex) {
        lex->input = NULL;
        lex->pos = 0;
        lex->cursor = '\0';
        lex->line = 1;
        lex->col = 1;
        
        // Should not crash
        lexer_advance(lex);
        TEST_PASS();
        
        free(lex);
    }
}
