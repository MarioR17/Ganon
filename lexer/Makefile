# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99
LDFLAGS = -lcheck -lm -lpthread

# macOS Homebrew paths for Check
BREW_PREFIX = $(shell brew --prefix)
CHECK_PREFIX = $(shell brew --prefix check)
CFLAGS += -I$(BREW_PREFIX)/include -I$(CHECK_PREFIX)/include
LDFLAGS += -L$(BREW_PREFIX)/lib -L$(CHECK_PREFIX)/lib

# Linux compatibility
ifeq ($(shell uname),Linux)
    LDFLAGS += -lsubunit
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
OBJ_DIR = obj

# Source files
SOURCES = $(SRC_DIR)/token.c $(SRC_DIR)/lexer.c
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Test files
TEST_SOURCES = $(TEST_DIR)/test_token.c $(TEST_DIR)/test_lexer.c $(TEST_DIR)/test_runner.c
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executables
TEST_EXEC = run_tests

# Default target
all: $(TEST_EXEC)

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile source objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_DIR)/%.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile test objects  
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link test executable
$(TEST_EXEC): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run tests with memory checking (Linux only)
test-mem: $(TEST_EXEC)
ifeq ($(shell uname),Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TEST_EXEC)
else
	@echo "Memory checking with Valgrind not available on macOS"
	@echo "Use 'make test-asan' for AddressSanitizer instead"
endif

# Run tests with AddressSanitizer
test-asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer
test-asan: LDFLAGS += -fsanitize=address
test-asan: clean $(TEST_EXEC)
	./$(TEST_EXEC)

# Run tests with coverage
test-coverage: CFLAGS += --coverage
test-coverage: LDFLAGS += --coverage
test-coverage: clean $(TEST_EXEC)
	./$(TEST_EXEC)
	gcov $(SOURCES)
	lcov --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1
	lcov --remove coverage.info '$(TEST_DIR)/*' --output-file coverage_filtered.info --ignore-errors unused
	genhtml coverage_filtered.info --output-directory coverage_html --branch-coverage
	@echo "Coverage report generated in coverage_html/index.html"
	@echo "Note: Only production code coverage is shown (test files excluded)"

# Install dependencies (Ubuntu/Debian)
install-deps-linux:
	sudo apt-get update
	sudo apt-get install -y check libcheck-dev valgrind lcov

# Install dependencies (macOS with Homebrew)
install-deps-mac:
	brew install check lcov

# Cross-platform dependency installer
install-deps:
ifeq ($(shell uname),Darwin)
	$(MAKE) install-deps-mac
else ifeq ($(shell uname),Linux)
	$(MAKE) install-deps-linux
else
	@echo "Unsupported platform. Please install check and lcov manually."
endif

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TEST_EXEC)
	rm -f *.log *.xml
	rm -f *.gcov *.gcda *.gcno *.info
	rm -rf coverage_html

# Clean and rebuild
rebuild: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  all           - Build test executable"
	@echo "  test          - Run all tests"
	@echo "  test-mem      - Run tests with Valgrind (Linux only)"
	@echo "  test-asan     - Run tests with AddressSanitizer (macOS/Linux)"
	@echo "  test-coverage - Run tests with coverage analysis"
	@echo "  install-deps  - Install dependencies (auto-detect platform)"
	@echo "  clean         - Remove build artifacts"
	@echo "  rebuild       - Clean and rebuild"
	@echo "  help          - Show this help message"

.PHONY: all test test-mem test-asan test-coverage install-deps install-deps-linux install-deps-mac clean rebuild help
