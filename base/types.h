// types.h - v1.00 - 2025 - Public domain
// A collection of fixed-width integer and floating-point type definitions.
// No OS/external dependencies; relies solely on C Runtime.
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

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

// Unsigned Integers
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed Integers (using 's' prefix)
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

// Signed Integers (using 'i' prefix as aliases)
typedef s8 i8;
typedef s16 i16;
typedef s32 i32;
typedef s64 i64;

// Pointer-sized Integers
typedef uintptr_t usize;
typedef intptr_t ssize;
typedef intptr_t isize;

// Floating-Point Types
// C does not have standard fixed-width float types like float16_t, float128_t.
// These are typically compiler-specific extensions or require external libraries.

typedef float f32;
typedef double f64;

// 'long double' is a standard C type, but its precision is implementation-defined.
// It can be 64-bit, 80-bit, or 128-bit depending on the compiler/platform.
typedef long double ldouble;

// For f16 (half-precision float), it's not standard C.
// GCC/Clang extension:
#if defined(__GNUC__) || defined(__clang__)
typedef __fp16 f16;
#else
// Not supported on this compiler
// typedef ... f16;
#endif

// For f128 (quad-precision float), it's not standard C, and 'long double' is not
// guaranteed to be 128-bit. True 128-bit floats often require compiler extensions.
// GCC/Clang extension:
#if defined(__GNUC__) || defined(__clang__)
typedef __float128 f128;
#else
// Not supported on this compiler
// typedef ... f128;
#endif

// Other types
typedef void *ptr;
typedef char *cstring;
typedef uint8_t byte;
typedef uint8_t *bytes;
typedef bool b8;

// String type

typedef struct
{
	char *data;
	usize len;
	usize cap;
} String;

// Allocates a new String with given capacity
static inline String String_new(usize cap)
{
	String s;
	s.data = (char *)malloc(cap);
	s.len = 0;
	s.cap = cap;
	if (s.data)
		s.data[0] = '\0';
	return s;
}

// Frees the memory used by the String
static inline void String_free(String *s)
{
	if (s && s->data)
	{
		free(s->data);
		s->data = NULL;
		s->len = 0;
		s->cap = 0;
	}
}

// Appends a C-string to the String, reallocating if needed
static inline int String_append(String *s, const char *src) {
	if (!s || !src)
		return -1;
	usize src_len = 0;
	while (src[src_len])
		src_len++;
	usize new_len = s->len + src_len;
	if (new_len + 1 > s->cap)
	{
		usize new_cap = (new_len + 1) * 2;
		char *new_data = (char *)realloc(s->data, new_cap);
		if (!new_data)
			return -1;
		s->data = new_data;
		s->cap = new_cap;
	}
	for (usize i = 0; i < src_len; ++i)
		s->data[s->len + i] = src[i];
	s->len = new_len;
	s->data[s->len] = '\0';
	return 0;
}

#endif // TYPEDEF_H
