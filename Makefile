# libb Makefile

CC      = clang
CFLAGS  = -Wall -Wextra -Wpedantic -std=c23 -g
CFLAGS += -fsanitize=address,undefined
LDFLAGS =

SRC_DIR   = src
TEST_DIR  = tests
BUILD_DIR = build

# Source files
SRCS = $(SRC_DIR)/arena.c $(SRC_DIR)/str.c $(SRC_DIR)/fs.c $(SRC_DIR)/vec.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Test executables
TESTS = $(BUILD_DIR)/test_arena $(BUILD_DIR)/test_str $(BUILD_DIR)/test_vec

.PHONY: all clean test

all: $(BUILD_DIR) $(OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test targets
$(BUILD_DIR)/test_arena: $(TEST_DIR)/test_arena.c $(BUILD_DIR)/arena.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_str: $(TEST_DIR)/test_str.c $(BUILD_DIR)/str.o $(BUILD_DIR)/arena.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/test_vec: $(TEST_DIR)/test_vec.c $(BUILD_DIR)/arena.o $(BUILD_DIR)/vec.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

test: $(TESTS)
	@echo "Running tests..."
	@echo ""
	@for t in $(TESTS); do $$t || exit 1; echo ""; done
	@echo "All tests passed!"

clean:
	rm -rf $(BUILD_DIR)
