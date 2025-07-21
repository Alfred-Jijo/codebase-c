
# Understanding Your Project's Makefile

This document explains the `Makefile` located in the root of your project, detailing its purpose, key variables, and how to modify it to manage your C codebase.

## Purpose

The `Makefile` automates the compilation, linking, and cleaning processes for your C project. It ensures that your code is built consistently for both debug and release configurations, and that executables are placed in the correct `bin/` subdirectories.

## Key Sections and How to Modify Them

### 1. Project Configuration

```Makefile

NAME = my\_program
VERSION = 0.0.0
PREFIX ?= $(HOME)/.local

```

* **`NAME`**: Defines the name of your executable. Change `my_program` to your desired application name.

* **`VERSION`**: Project version (informational).

* **`PREFIX`**: Installation prefix (used for `make install`, if implemented).

### 2. Compiler Settings

```

GCC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99

# CFLAGS = -Wall -Wextra -Werror -pedantic -Wno-unused-parameter -Wshadow -std=c99 -fsanitize=address

```

* **`GCC`**: Specifies the C compiler to use. Defaults to `gcc`. You can change this if you use a different compiler (e.g., `clang`).

* **`CFLAGS`**: Compiler flags applied to all compilations.

  * **Adding/Removing Flags**: You can add or remove flags here. For example, to enable AddressSanitizer for memory error detection, uncomment the line with `-fsanitize=address`.

### 3. Source Files and Object Files

```

SRC = src/main.c
OBJ = $(SRC:%.c=%.o)

````

* **`SRC`**: **This is where you add new source files (`.c` files) to your project.**

  * **How to Add Source Files**: If you create a new file like `src/module.c` or `base/utility.c`, you must add it to this list:

    ```
    SRC = src/main.c src/module.c base/utility.c
    
    ```

  * The `OBJ` variable automatically generates the corresponding object file names (`.o`) from this list.

### 4. Include Paths

````

INCLUDE = -Ibase -Iinclude

````

* **`INCLUDE`**: Specifies directories where the compiler should search for header files (`.h`).

  * **How to Add Include Directories**: If you add a new directory containing headers (e.g., `lib/external_lib/include`), you need to add its path here using the `-I` flag:

    ```
    INCLUDE = -Ibase -Iinclude -Ilib/external_lib/include
    
    ```

### 5. Build Directories

````

BIN\_DIR\_DEBUG = bin/debug
BIN\_DIR\_RELEASE = bin/release
BUILD\_DIR = build

```

* These variables define the output directories for debug executables, release executables, and intermediate object files, respectively. You typically won't need to change these unless you want a different directory structure for your binaries or build artifacts.

## How to Use the Makefile

Open your terminal in the root directory of your project (where the `Makefile` is located) and run the following commands:

* **`make`** or **`make all`**:

  * Cleans the project (`make clean`).

  * Builds the optimized release version of your executable (`my_program`) and places it in `bin/release/`.

  * Runs the release executable.

* **`make debug`**:

  * Compiles your project with debugging symbols (`-g`).

  * Creates an executable named `my_program_debug` in `bin/debug/`. Use this version for debugging with tools like `gdb`.

* **`make release`**:

  * Compiles your project with optimizations (`-O2`) and without debugging symbols.

  * Creates an executable named `my_program` in `bin/release/`. This is the version suitable for deployment.

* **`make run`**:

  * Ensures the release executable is built.

  * Executes the `my_program` from `bin/release/`.

* **`make clean`**:

  * Removes all generated object files from `build/`.

  * Removes all executables from `bin/debug/` and `bin/release/`. This is useful for starting a fresh build.

## Compilation Rule (`.c` to `.o`)

```

$(BUILD\_DIR)/%.o: %.c
@mkdir -p $(@D)
@echo "Compiling $\< to $@"
$(GCC) -c $\< -o $@ $(CFLAGS) $(INCLUDE)

```

This rule tells `make` how to compile any `.c` source file into an object file (`.o`). It ensures that object files are placed in the `build/` directory and that necessary subdirectories within `build/` are created automatically.
