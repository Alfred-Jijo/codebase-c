// macros.h - 2025 - Public domain
// A collection of macros for determining the compilation context (OS, compiler, architecture).
// No OS/external dependencies; relies solely on pre-defined compiler macros.
//
// This file is part of the C project template by Alfred Jijo.
//
// LICENSE
//   This software is in the public domain. Where that is not legally possible,
//   this software is licensed under the MIT License.
//
//   MIT License
//
//   Copyright (c) 2025 Alfred Jijo
//
//   Permission is hereby granted, free of charge, to any person obtaining a copy
//   of this software and associated documentation files (the "Software"), to deal
//   in the Software without restriction, including without limitation the rights
//   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//   copies of the Software, and to permit persons to whom the Software is
//   furnished to do so, subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.

#ifndef CTXMCS_H
#define CTXMCS_H

//
// OS-specific headers macro
//
#if defined(_WIN32)
# ifndef WIN32_LEAN_AND_MEAN
#  define WIN32_LEAN_AND_MEAN
# endif
# define OS_HEADERS \
    #include <windows.h>
#elif defined(__linux__)
# define OS_HEADERS \
    #include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
# define OS_HEADERS \
    #include <unistd.h>
#else
# define OS_HEADERS
#endif

#include <stdio.h>

//
// Compiler Detection
//
#if defined(__clang__)
# define COMPILER_CLANG 1
# define COMPILER_NAME "Clang"
#elif defined(__GNUC__)
# define COMPILER_GCC 1
# define COMPILER_NAME "GCC"
#elif defined(_MSC_VER)
# define COMPILER_MSVC 1
# define COMPILER_NAME "MSVC"
#else
# error "Compiler not supported"
#endif

//
// Operating System Detection
//
#if defined(_WIN32)
# define OS_WINDOWS 1
# define OS_NAME "Windows"
#elif defined(__linux__)
# define OS_LINUX 1
# define OS_NAME "Linux"
#elif defined(__APPLE__) && defined(__MACH__)
# define OS_MAC 1
# define OS_NAME "macOS"
#else
# error "Operating system not supported"
#endif

//
// Architecture Detection
//
#if defined(_M_X64) || defined(__x86_64__)
# define ARCH_X64 1
# define ARCH_NAME "x86-64"
#elif defined(_M_IX86) || defined(__i386__)
# define ARCH_X86 1
# define ARCH_NAME "x86"
#elif defined(_M_ARM64) || defined(__aarch64__)
# define ARCH_ARM64 1
# define ARCH_NAME "ARM64"
#elif defined(_M_ARM) || defined(__arm__)
# define ARCH_ARM 1
# define ARCH_NAME "ARM"
#else
# error "Architecture not supported"
#endif

//
// Build Configuration
//
#if defined(NDEBUG)
# define BUILD_RELEASE 1
# define BUILD_NAME "Release"
#else
# define BUILD_DEBUG 1
# define BUILD_NAME "Debug"
#endif

//
// Endianness Detection
//
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) || defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__)
# define ENDIAN_LITTLE 1
# define ENDIAN_NAME "Little Endian"
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) || defined(__BIG_ENDIAN__)
# define ENDIAN_BIG 1
# define ENDIAN_NAME "Big Endian"
#else
# error "Could not determine endianness"
#endif

//
// C Standard Version
//
#if defined(__STDC_VERSION__)
# if __STDC_VERSION__ >= 202311L
#  define C_STANDARD 23
#  define C_STANDARD_NAME "C23"
# elif __STDC_VERSION__ >= 201710L
#  define C_STANDARD 17
#  define C_STANDARD_NAME "C17"
# elif __STDC_VERSION__ >= 201112L
#  define C_STANDARD 11
#  define C_STANDARD_NAME "C11"
# elif __STDC_VERSION__ >= 199901L
#  define C_STANDARD 99
#  define C_STANDARD_NAME "C99"
# else
#  define C_STANDARD 89 // C89/C90
#  define C_STANDARD_NAME "C89"
# endif
#else
# define C_STANDARD 99 // Default to C99
# define C_STANDARD_NAME "C99"
#endif

//
// Utility Macros
//
#if COMPILER_MSVC
# define FORCE_INLINE __forceinline
#elif COMPILER_GCC || COMPILER_CLANG
# define FORCE_INLINE __attribute__((always_inline)) inline
#else
# define FORCE_INLINE inline
#endif

// Stringification macros for C_STANDARD
#define _STRINGIFY(x) #x
#define _TO_STRING(x) _STRINGIFY(x)

//
// Context Information
//

// Helper to get string length without <string.h>
static
inline
size_t
_strlen(const char* str)
{
    size_t len = 0;
    while (str[len]) { len++; }
    return len;
}

static
inline
void
print(const char* message)
{
    fputs(message, stdout);
}

static
inline
void
print_context_info(void)
{
    print("Compilation Context:\n");
    print("    Compiler: " COMPILER_NAME "\n");
    print("    OS: " OS_NAME "\n");
    print("    Architecture: " ARCH_NAME "\n");
    print("    Endianness: " ENDIAN_NAME "\n");
    print("    Build: " BUILD_NAME "\n");
    print("    C Standard: " C_STANDARD_NAME "\n");
}

// Define a debug break macro for cross-platform use
#if COMPILER_MSVC
# define debug_break() __debugbreak()
#elif COMPILER_GCC || COMPILER_CLANG
# define debug_break() __builtin_trap()
#else
# define debug_break() (*(volatile int*)0 = 0) // Fallback for unsupported compilers
#endif

// The main ASSERT macro
#if BUILD_DEBUG
# define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            print("Assertion failed: " #expr "\n"); \
            print("File: " __FILE__ "\n"); \
            print("Line: " _TO_STRING(__LINE__) "\n"); \
            debug_break(); \
        } \
    } while (0)
#else
# define ASSERT(expr) // In release builds, assertions do nothing
#endif

// Define a macro to check if a pointer is NULL
#define ASSERT_NOT_NULL(ptr) \
    do { \
	if ((ptr) == NULL) { \
	    print("Assertion failed: " #ptr " is NULL\n"); \
	    print("File: " __FILE__ "\n"); \
	    print("Line: " _TO_STRING(__LINE__) "\n"); \
	    debug_break(); \
	} \
    } while (0)

// Define a macro to check if two pointers are equal
#define ASSERT_EQUAL(ptr1, ptr2) \
    do { \
	if ((ptr1) != (ptr2)) { \
	    print("Assertion failed: " #ptr1 " != " #ptr2 "\n"); \
	    print("File: " __FILE__ "\n"); \
	    print("Line: " _TO_STRING(__LINE__) "\n"); \
	    debug_break(); \
	} \
    } while (0)


// Linkage macros
#define INTERNAL static
#define EXTERNAL extern

// Symbol visibility macros for shared libraries
#if defined(__GNUC__) || defined(__clang__)
# define API_EXPORT __attribute__((visibility("default")))
# define API_LOCAL  __attribute__((visibility("hidden")))
#elif defined(_MSC_VER)
# define API_EXPORT __declspec(dllexport)
# define API_LOCAL  __declspec(dllimport)
#else
# define API_EXPORT
# define API_LOCAL
#endif

// C linkage macros for C++
#ifdef __cplusplus
# define C_LINKAGE extern "C"
# define C_LINKAGE_BEGIN extern "C" {
# define C_LINKAGE_END }
#else
# define C_LINKAGE
# define C_LINKAGE_BEGIN
# define C_LINKAGE_END
#endif

// Define a macro for deprecation warnings
#if defined(__GNUC__) || defined(__clang__)
# define DEPRECATED(msg) __attribute__((deprecated(msg)))
#elif defined(_MSC_VER)
# define DEPRECATED(msg) __declspec(deprecated(msg))
#else
# define DEPRECATED(msg)
#endif

#endif // CTXMCS_H
