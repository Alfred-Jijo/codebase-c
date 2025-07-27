# Understanding Your Project's Makefile

This document explains the `Makefile` located in the root of your project, detailing its purpose, key variables, and how to modify it to manage your C codebase.

## Purpose

The `Makefile` automates the compilation, linking, and cleaning processes for your C project. It ensures that your code is built consistently for both debug and release configurations, and that executables are placed in the correct `bin/` subdirectories.

## Key Sections and How to Modify Them

### 1. Project Configuration

```makefile
NAME = codebase
VERSION = 0.4.3
PREFIX ?= $(HOME)/.local
```
- **`NAME`**: Defines the name of your executable. Change as needed.
- **`VERSION`**: Project version (informational).
- **`PREFIX`**: Installation prefix (used for `make install`, if implemented).

### 2. Compiler Settings

```makefile
GCC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99
```
- **`GCC`**: The C compiler to use. Defaults to `gcc`. Change to `clang` if desired.
- **`CFLAGS`**: Compiler flags for all builds. Add `-g` for debug, `-O2 -DNDEBUG` for release.

### 3. Source Files and Object Files

```makefile
SRC = src/main.c
OBJ = $(SRC:src/%.c=build/%.o)
```
- **`SRC`**: Add all your `.c` source files here. For example:
  ```
  SRC = src/main.c src/foo.c lib/bar.c
  ```
- **`OBJ`**: Automatically generates object file names in `build/`.

### 4. Include Paths

```makefile
INCLUDE = -Ibase -Iinclude
```
- Add any additional include directories here, e.g. `-Ilib/mylib/include`.

### 5. Build Directories

```makefile
BIN_DIR_DEBUG = bin/debug
BIN_DIR_RELEASE = bin/release
BUILD_DIR = build
```
- These control where debug/release binaries and object files are placed.

### 6. Test Targets

```makefile
TESTDIR = test
TESTS = $(TESTDIR)/test_macros.c
TESTBINS = $(TESTS:$(TESTDIR)/%.c=$(TESTDIR)/%.exe)
TESTALLSRC = $(TESTDIR)/test_all.c
TESTALLBIN = $(TESTDIR)/test_all.exe
```
- Add new test `.c` files to `TESTS` as you add more tests.

### 7. Directory and .gitignore Management

The Makefile ensures that `build/`, `bin/debug/`, and `bin/release/` directories exist and contain a `.gitignore` file with:
```
*
!.gitignore
!*.c
```
This keeps build artifacts out of version control.

## How to Use the Makefile

Open your terminal in the root directory of your project (where the `Makefile` is located) and run the following commands:

- **`make`** or **`make all`**:  
  Cleans the project, builds the optimized release version, and places it in `bin/release/`.

- **`make debug`**:  
  Builds with debugging symbols, outputting to `bin/debug/NAME_debug`.

- **`make release`**:  
  Builds with optimizations, outputting to `bin/release/NAME`.

- **`make run`**:  
  Builds (if needed) and runs the release executable.

- **`make run_debug`**:  
  Builds (if needed) and runs the debug executable.

- **`make clean`**:  
  Removes all generated object files and executables.

- **`make test`**:  
  Builds and runs all test executables in the `test/` directory.

- **`make test_all`**:  
  Builds all tests and runs the test runner (`test_all.exe`).

- **`make test_testname`**:  
  Builds and runs a specific test, e.g. `make test_test_macros`.

## Tips and Tricks

- **Adding New Source Files:**  
  Add new `.c` files to `SRC`. The object files will be handled automatically.

- **Adding New Tests:**  
  Add new test `.c` files to `TESTS`. They will be built and run with `make test`.

- **Adding Include Directories:**  
  Add new `-I` paths to `INCLUDE` as needed.

- **Debugging:**  
  Use `make debug` to build with debug symbols, and `make run_debug` to run the debug build.

- **Custom Compiler:**  
  Override `GCC` on the command line:  
  ```
  make GCC=clang
  ```

- **Sanitizers:**  
  Add `-fsanitize=address` to `CFLAGS` for AddressSanitizer support.

- **Parallel Builds:**  
  Use `make -jN` to build with N parallel jobs.

- **Install/Uninstall:**  
  If you add install/uninstall targets, use `PREFIX` for the install location.

## Compilation Rule (`.c` to `.o`)

```makefile
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	@echo "Compiling $< to $@"
	$(GCC) -c $< -o $@ $(CFLAGS) $(INCLUDE)
```
This rule compiles any `.c` file in `src/` to an object file in `build/`, creating directories as needed.

## Example Workflow

1. Build and run the release executable:
   ```
   make
   make run
   ```
2. Build and run the debug executable:
   ```
   make debug
   make run_debug
   ```
3. Clean all build artifacts:
   ```
   make clean
   ```
4. Run all tests:
   ```
   make test
   ```
5. Run a specific test:
   ```
   make test_test_macros
   ```

---

For more advanced build setups, consider using CMake or another build system, but for most small to medium C projects, this Makefile should suffice.
