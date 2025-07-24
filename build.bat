@echo off
setlocal

REM --- Project Configuration ---
set NAME=codebase
set VERSION=0.4.3

REM --- Directory Configuration ---
set SRCDIR_APP=src
set SRCDIR_BASE=base
set SRCDIR_LIB=lib
set BUILDDIR=build
set BINDIR=bin

REM --- Compiler and Flags ---
REM Note: Ensure that 'cl.exe' is in your PATH.
REM You might need to run this from a "Developer Command Prompt for VS".
set CC=cl
set CFLAGS=/W4 /WX /Zi /nologo /I%SRCDIR_BASE%

REM --- Source Files ---
set SOURCES=%SRCDIR_APP%\main.c

REM --- Object Files ---
set OBJECTS=%BUILDDIR%\main.obj

REM --- Test Configuration ---
set TESTDIR=test
set TESTS=%TESTDIR%\test_macros.c
set TESTBIN=%BINDIR%\test_macros.exe
set TESTALLSRC=%TESTDIR%\test_all.c
set TESTALLBIN=%BINDIR%\test_all.exe

REM --- Default Target: Build the project ---
if "%1"=="" goto build
if "%1"=="all" goto build
if "%1"=="clean" goto clean
if "%1"=="run" goto run
if "%1"=="test" goto test
if "%1"=="test_all" goto test_all
echo "Unknown command: %1"
goto:eof

:build
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    call :clean
    echo "Starting build..."
    if not exist %BINDIR% (
        mkdir %BINDIR%
        echo *>%BINDIR%\.gitignore
        echo !.gitignore>>%BINDIR%\.gitignore
        echo !*.c>>%BINDIR%\.gitignore
    )
    if not exist %BUILDDIR% (
        mkdir %BUILDDIR%
        echo *>%BUILDDIR%\.gitignore
        echo !.gitignore>>%BUILDDIR%\.gitignore
        echo !*.c>>%BUILDDIR%\.gitignore
    )

    echo "Compiling %SOURCES%..."
    %CC% %CFLAGS% /c "%SOURCES%" /Fo"%OBJECTS%"

    echo "Linking %NAME%..."
    %CC% "%OBJECTS%" /link /OUT:"%BINDIR%\%NAME%.exe"

    echo "Build complete: %BINDIR%\%NAME%.exe"
    goto:eof

:run
    call :build
    echo "Running %NAME%..."
    %BINDIR%\%NAME%.exe
    goto:eof

:clean
    echo "Cleaning build artifacts..."
    if exist %BUILDDIR% rmdir /s /q %BUILDDIR%
    if exist %BINDIR% rmdir /s /q %BINDIR%
    echo "Clean complete."
    goto:eof

:test
    if "%2"=="" (
        echo "Building and running all tests..."
        call :test_all
        goto:eof
    )
    if not exist %BINDIR% (
        mkdir %BINDIR%
        echo *>%BINDIR%\.gitignore
        echo !.gitignore>>%BINDIR%\.gitignore
        echo !*.c>>%BINDIR%\.gitignore
    )
    set TESTSRC=%TESTDIR%\%2.c
    set TESTEXE=%BINDIR%\%2.exe
    if not exist %BINDIR% mkdir %BINDIR%
    echo "Compiling %TESTSRC%..."
    %CC% %CFLAGS% /Fe"%TESTEXE%" "%TESTSRC%"
    if exist "%TESTEXE%" (
        echo "Running %TESTEXE%..."
        "%TESTEXE%"
    ) else (
        echo "Test build failed: %TESTSRC%"
    )
    goto:eof

:test_all
    if not exist %BINDIR% (
        mkdir %BINDIR%
        echo *>%BINDIR%\.gitignore
        echo !.gitignore>>%BINDIR%\.gitignore
        echo !*.c>>%BINDIR%\.gitignore
    )
    if not exist %BINDIR% mkdir %BINDIR%
    echo "Compiling all tests..."
    %CC% %CFLAGS% /Fe"%TESTBIN%" "%TESTS%"
    %CC% %CFLAGS% /Fe"%TESTALLBIN%" "%TESTALLSRC%"
    echo "Running all tests..."
    pushd %BINDIR%
    test_all.exe
    popd
    goto:eof
