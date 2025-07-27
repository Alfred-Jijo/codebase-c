# Understanding Your Project's `build.bat`

This document explains the `build.bat` script found in your project root.  
It automates building, cleaning, running, and testing your C codebase on Windows using the MSVC toolchain.

---

## Key Sections and How to Modify Them

### 1. Project Configuration

```bat
set NAME=codebase
set VERSION=0.4.3
```
- **NAME**: The name of your executable.
- **VERSION**: Project version (informational).

### 2. Directory Configuration

```bat
set SRCDIR_APP=src
set SRCDIR_BASE=base
set SRCDIR_LIB=lib
set BUILDDIR=build
set BINDIR=bin
```
- Change these if you reorganize your source or output directories.

### 3. Compiler and Flags

```bat
set CC=cl
set CFLAGS=/W4 /WX /Zi /nologo /I%SRCDIR_BASE%
```
- **CC**: The compiler (MSVC's `cl.exe`).
- **CFLAGS**: Compiler flags.  
  - `/W4` enables high warning level.
  - `/WX` treats warnings as errors.
  - `/Zi` enables debug info.
  - `/I%SRCDIR_BASE%` adds the base directory to the include path.

### 4. Source and Object Files

```bat
set SOURCES=%SRCDIR_APP%\main.c
set OBJECTS=%BUILDDIR%\main.obj
```
- Add new source files to `SOURCES` as needed.

### 5. Test Configuration

```bat
set TESTDIR=test
set TESTS=%TESTDIR%\test_macros.c
set TESTBIN=%BINDIR%\test_macros.exe
set TESTALLSRC=%TESTDIR%\test_all.c
set TESTALLBIN=%BINDIR%\test_all.exe
```
- Add new test files to `TESTS` and update as your test suite grows.

---

## How to Use `build.bat`

Open a "Developer Command Prompt for VS" in your project root and run:

- **Build the project:**  
  ```
  build.bat
  ```
  or
  ```
  build.bat all
  ```
  - Cleans previous builds, compiles sources, links the executable.

- **Run the project:**  
  ```
  build.bat run
  ```
  - Builds (if needed) and runs the executable.

- **Clean build artifacts:**  
  ```
  build.bat clean
  ```
  - Removes all files in `build` and `bin` directories.

- **Run all tests:**  
  ```
  build.bat test
  ```
  or
  ```
  build.bat test_all
  ```
  - Builds and runs all tests in the test suite.

- **Run a specific test:**  
  ```
  build.bat test test_macros
  ```
  - Builds and runs `test_macros.c` as an individual test.

---

## Directory and `.gitignore` Management

When creating `bin` or `build` directories, the script also creates a `.gitignore` file inside each, containing:
```
*
!.gitignore
!*.c
```
This keeps build artifacts out of version control.

---

## Tips and Tricks

- **Add more source files:**  
  Update `SOURCES` and `OBJECTS` variables.
- **Add more tests:**  
  Update `TESTS` and add corresponding build/run logic if needed.
- **Change compiler flags:**  
  Edit `CFLAGS` for stricter warnings, optimizations, or debug info.
- **Run from the right environment:**  
  Always use a "Developer Command Prompt for VS" so `cl.exe` is available.
- **Debugging:**  
  Add `/Od` to `CFLAGS` for no optimization, or `/Zi` for debug info.
- **Custom build steps:**  
  You can add more targets or logic by editing the batch file.

---

## Example Workflow

1. Build and run the release executable:
   ```
   build.bat
   build.bat run
   ```
2. Clean all build artifacts:
   ```
   build.bat clean
   ```
3. Run all tests:
   ```
   build.bat test
   ```
4. Run a specific test:
   ```
   build.bat test test_macros
   ```

---

**Note:**  
This script is designed for MSVC (`cl.exe`).  
For GCC/Clang or other platforms, use the provided `Makefile` instead.

> **Tip:** Run these commands from a "Developer Command Prompt for VS" to ensure `cl.exe` is in your PATH.
