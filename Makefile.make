NAME = codebase
VERSION = 0.4.2
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99

SRC = src/main.c
OBJ = $(SRC:%.c=%.o)

INCLUDE = -Ibase -Iinclude

BIN_DIR_DEBUG = bin/debug
BIN_DIR_RELEASE = bin/release
BUILD_DIR = build

.PHONY: all clean run debug release

all: clean $(BIN_DIR_RELEASE)/$(NAME) run

debug: CFLAGS += -g
debug: $(BUILD_DIR) $(BIN_DIR_DEBUG) $(OBJ)
	@echo "Building debug executable..."
	$(GCC) $(OBJ) -o $(BIN_DIR_DEBUG)/$(NAME)_debug $(CFLAGS) $(INCLUDE)
	@echo "Debug executable built: $(BIN_DIR_DEBUG)/$(NAME)_debug"

release: CFLAGS += -O2 -DNDEBUG
release: $(BUILD_DIR) $(BIN_DIR_RELEASE) $(OBJ)
	@echo "Building release executable..."
	$(GCC) $(OBJ) -o $(BIN_DIR_RELEASE)/$(NAME) $(CFLAGS) $(INCLUDE)
	@echo "Release executable built: $(BIN_DIR_RELEASE)/$(NAME)"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $< to $@"
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(OBJ): $(BUILD_DIR)/%.o: %.c
	$(GCC) -c $< -o $(BUILD_DIR)/$(@F) $(CFLAGS) $(INCLUDE)

run: $(BIN_DIR_RELEASE)/$(NAME)
	@echo "Running $(NAME)..."
	./$(BIN_DIR_RELEASE)/$(NAME)

clean:
	@echo "Cleaning project..."
	$(RM) -r $(BUILD_DIR) $(BIN_DIR_DEBUG) $(BIN_DIR_RELEASE)
	@echo "Clean complete."

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BIN_DIR_DEBUG):
	@mkdir -p $(BIN_DIR_DEBUG)

$(BIN_DIR_RELEASE):
	@mkdir -p $(BIN_DIR_RELEASE)
