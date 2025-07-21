@echo off
setlocal

REM --- Project Configuration ---
set NAME=codebase
set VERSION=0.4.2

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

REM --- Default Target: Build the project ---
if "%1"=="" goto build
if "%1"=="all" goto build
if "%1"=="clean" goto clean
if "%1"=="run" goto run
echo "Unknown command: %1"
goto:eof

:build
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    call :clean
    echo "Starting build..."
    if not exist %BINDIR% mkdir %BINDIR%
    if not exist %BUILDDIR% mkdir %BUILDDIR%

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
