NAME = codebase
VERSION = 0.4.3
PREFIX ?= $(HOME)/.local

GCC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99

SRC = src/main.c
OBJ = $(SRC:src/%.c=build/%.o)

INCLUDE = -Ibase -Iinclude

BIN_DIR_DEBUG = bin/debug
BIN_DIR_RELEASE = bin/release
BUILD_DIR = build

TESTDIR = test
TESTS = $(TESTDIR)/test_macros.c
TESTBINS = $(TESTS:$(TESTDIR)/%.c=$(TESTDIR)/%.exe)
TESTALLSRC = $(TESTDIR)/test_all.c
TESTALLBIN = $(TESTDIR)/test_all.exe

.PHONY: all clean run debug release test test_all install uninstall

all: release

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@echo "Compiling $< to $@"
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(BUILD_DIR):
	@mkdir -p $@
	@echo '*' > $@/.gitignore
	@echo '!.gitignore' >> $@/.gitignore
	@echo '!*.c' >> $@/.gitignore

$(BIN_DIR_DEBUG):
	@mkdir -p $@
	@echo '*' > $@/.gitignore
	@echo '!.gitignore' >> $@/.gitignore
	@echo '!*.c' >> $@/.gitignore

$(BIN_DIR_RELEASE):
	@mkdir -p $@
	@echo '*' > $@/.gitignore
	@echo '!.gitignore' >> $@/.gitignore
	@echo '!*.c' >> $@/.gitignore

$(BIN_DIR_RELEASE)/$(NAME): $(OBJ) | $(BIN_DIR_RELEASE)
	@echo "Linking $@"
	$(GCC) $^ -o $@ $(CFLAGS) $(INCLUDE)

$(BIN_DIR_DEBUG)/$(NAME)_debug: $(OBJ) | $(BIN_DIR_DEBUG)
	@echo "Linking $@"
	$(GCC) $^ -o $@ $(CFLAGS) -g $(INCLUDE)

debug: CFLAGS += -g
debug: $(BIN_DIR_DEBUG)/$(NAME)_debug
	@echo "Debug executable built: $(BIN_DIR_DEBUG)/$(NAME)_debug"

release: CFLAGS += -O2 -DNDEBUG
release: $(BIN_DIR_RELEASE)/$(NAME)
	@echo "Release executable built: $(BIN_DIR_RELEASE)/$(NAME)"

run: $(BIN_DIR_RELEASE)/$(NAME)
	@echo "Running $(NAME)..."
	./$(BIN_DIR_RELEASE)/$(NAME)

run_debug: debug
	@echo "Running debug executable..."
	./$(BIN_DIR_DEBUG)/$(NAME)_debug

clean:
	@echo "Cleaning project..."
	$(RM) -r $(BUILD_DIR) $(BIN_DIR_DEBUG) $(BIN_DIR_RELEASE)
	@echo "Clean complete."

# Test rules
$(TESTDIR)/%.exe: $(TESTDIR)/%.c
	$(GCC) $(CFLAGS) $(INCLUDE) $< -o $@

$(TESTALLBIN): $(TESTALLSRC)
	$(GCC) $(CFLAGS) $(INCLUDE) $< -o $@

test: $(TESTBINS)
	@echo "Running all tests..."
	@for t in $(TESTBINS); do ./$$t; done

test_all: $(TESTBINS) $(TESTALLBIN)
	@echo "Running test_all..."
	@./$(TESTALLBIN)

test_%: $(TESTDIR)/test_%.c
	$(GCC) $(CFLAGS) $(INCLUDE) $< -o $(TESTDIR)/test_$*.exe
	@./$(TESTDIR)/test_$*.exe

install: $(BIN_DIR_RELEASE)/$(NAME)
	@echo "Installing $(NAME) to $(PREFIX)/bin"
	@mkdir -p $(PREFIX)/bin
	@cp $(BIN_DIR_RELEASE)/$(NAME) $(PREFIX)/bin/$(NAME)
	@echo "Install complete."

uninstall:
	@echo "Uninstalling $(NAME) from $(PREFIX)/bin"
	@rm -f $(PREFIX)/bin/$(NAME)
	@echo "Uninstall complete."
