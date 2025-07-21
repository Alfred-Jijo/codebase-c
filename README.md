# My New C Project Template

This is a basic C project template designed to provide a clean and organized starting point for your C development. 

## Directory Structure

.
├── src/            # Application-specific source files (e.g., main.c)
│   └── main.c
├── base/           # Base layer code (now contains only types.h)
│   └── types.h     # Fixed-width type definitions (u8, s16, f32, etc.)
├── lib/            # Library source files (currently empty)
├── docs/           # Project documentation
├── build/          # (Generated) Intermediate object files (.o)
├── bin/            # (Generated) The final executable is placed here
├── Makefile        # Defines build rules, compilation flags, and common commands
├── README.md       # This file
└── LICENSE         # Placeholder for your project's license


## How to Use This Template

1.  **Clone or Download**: Get this template to your local machine.
    * If you're using Git: `git clone <URL_TO_THIS_REPO> my_new_project`
    * Then `cd my_new_project`
3.  **Customize**:
    * Rename `my_new_project` to your desired project name.
    * Modify `src/main.c` and other files to suit your project's needs.
    * Add new `.c` files to `src/` or `lib/` (and their subdirectories) and their corresponding `.h` files to `base/` or alongside their `.c` files in `lib/` as appropriate.
    * **Important**: If you add new source files, you **MUST** update the `SOURCES` variable in the `Makefile` to include them.
    * **Update the `INCLUDE` variable in the `Makefile`** if your new module/library has public headers that need to be found by other modules (e.g., `-Ibase/` or `-Ilib/my_new_lib/include`).
4.  **Build**: Open your terminal in the project's root directory and run:
    ```bash
    make
    ```
    This will compile your source code and create the executable in the `bin/` directory.

## Available Makefile Commands

* `make all` (or just `make`): Compiles the project and creates the executable.
* `make run`: Compiles the project (if not already built) and then runs the executable.
* `make clean`: Removes all generated build files (`.o` files and the executable).
* `make debug`: Compiles the project with debugging symbols and starts `gdb` (GNU Debugger) with your executable.
* `make install`: Installs the compiled executable to `$(PREFIX)/bin` (defaults to `~/.local/bin`). P.S. Ensure `$(PREFIX)/bin` is in your `PATH` environment variable.
* `make uninstall`: Removes the installed executable.

## Extending the Template

* **Base Layer (`base/`)**: This directory is intended for fundamental, highly portable code that has no dependencies beyond the standard C Runtime.
* **Application Source (`src/`)**: This is where your main application logic resides. It can depend on `base/` and `lib/`.
* **Libraries (`lib/`)**: This directory is for reusable code modules that might have their own internal structure.
* **Adding new source files**:
    * For application-specific code, place `.c` files in `src/`.
    * For base layer headers (like `types.h`), place them in `base/`.
    * For new libraries, create a new subdirectory in `lib/` (e.g., `lib/my_new_lib/src/my_new_lib.c` and `lib/my_new_lib/include/my_new_lib.h`).
    * **Crucially, update the `SOURCES` variable in the `Makefile`** to include the paths to your new `.c` files.
    * **Update the `INCLUDE` variable in the `Makefile`** if your new module/library has public headers that need to be found by other modules.
* **Adding external libraries**: You might need to add `-L/path/to/lib -l<library_name>` to the `LDFLAGS` variable in the `Makefile`.
* **More complex builds**: For very large projects, consider using a more advanced build system like CMake, but for most small to medium C projects, this `Makefile` should suffice.

## License

See the `LICENSE` file for details.

