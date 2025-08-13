CC = gcc
CFLAGS = -Wall -Wextra -std=c99
COVERAGE_FLAGS = --coverage -O0 -g

UNITY_DIR = ../unity
LEXER_DIR = ./
TEST_DIR = tests
COVERAGE_DIR = coverage
BUILD_DIR = build

UNITY_SRC = $(UNITY_DIR)/unity.c
LEXER_SRC = $(LEXER_DIR)/src/lexer.c $(LEXER_DIR)/src/token.c
TEST_SRC = $(TEST_DIR)/test_runner.c $(TEST_DIR)/test_lexer.c $(TEST_DIR)/test_token.c

INCLUDES = -I$(UNITY_DIR) -I$(LEXER_DIR)/include

all: test

test:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRC) $(LEXER_SRC) $(UNITY_SRC) -o $(BUILD_DIR)/test_runner
	cd $(BUILD_DIR) && ./test_runner

test-coverage:
	mkdir -p $(BUILD_DIR) $(COVERAGE_DIR)
	cp -r $(LEXER_DIR) $(UNITY_DIR) $(TEST_DIR) $(BUILD_DIR)/
	cd $(BUILD_DIR) && $(CC) $(CFLAGS) $(COVERAGE_FLAGS) -I$(UNITY_DIR) -I$(LEXER_DIR)/include \
		$(TEST_DIR)/test_runner.c $(TEST_DIR)/test_lexer.c $(TEST_DIR)/test_token.c \
		$(LEXER_DIR)/src/lexer.c $(LEXER_DIR)/src/token.c $(UNITY_DIR)/unity.c \
		-o test_runner_coverage
	cd $(BUILD_DIR) && ./test_runner_coverage
	lcov --capture --directory $(BUILD_DIR) --output-file $(COVERAGE_DIR)/coverage.info
	lcov --remove $(COVERAGE_DIR)/coverage.info '/usr/*' '*/unity/*' '*/tests/*' --output-file $(COVERAGE_DIR)/coverage_filtered.info
	genhtml $(COVERAGE_DIR)/coverage_filtered.info --output-directory $(COVERAGE_DIR)/html --title "Code Coverage Report"
	@echo "Coverage HTML report: $(COVERAGE_DIR)/html/index.html"

clean:
	rm -rf $(BUILD_DIR) $(COVERAGE_DIR) $(TEST_DIR)/temp
	rm -f *.gcov *.gcda *.gcno
	rm -f test_*.txt

help:
	@echo "Available targets:"
	@echo "  test           - Build and run tests"
	@echo "  test-coverage  - Run tests with coverage and generate HTML report"
	@echo "  clean          - Remove all generated files"
	@echo "  help           - Show this help"

.PHONY: all test test-coverage clean help
