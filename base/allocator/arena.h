#ifndef ARENA_H
#define ARENA_H

#include "types.h"

// Defining ARENA memory allocator
#define ARENA_MALLOC malloc
#define ARENA_FREE free
#define ARENA_REALLLOC realloc
#define ARENA_MEMCPY memcpy

// Defining return values for ARENA functions
#define ARENA_SUCCESS 0
#define ARENA_NOT_ENOUGH_SPACE -2
#define ARENA_INVALID_SIZE -3
#define ARENA_NULL_POINTER -4
#define ARENA_NOT_INITIALIZED -5
#define ARENA_ALREADY_INITIALIZED -6
#define ARENA_EMPTY -7

// Arena memory allocator
typedef struct Arena Arena;

// Initializes the arena with a specified size
void *
arena_init(Arena *arena, const usize size);

// Allocates a block of memory from the arena
void *
arena_alloc(Arena *arena, const usize size);

// Frees the arena and its memory block
void
arena_free(const Arena *arena);

// Resets the arena, freeing all allocated memory but keeping the arena
// structure intact
void
arena_reset(Arena *arena);

// Checks if the arena has enough memory to allocate a block of the specified
// size
b8
arena_has_space(const Arena *arena, const usize size);

// Gets the amount of memory currently used in the arena
usize
arena_used(const Arena *arena);

// Gets the total size of the arena
usize
arena_total_size(const Arena *arena);

// Gets the remaining free space in the arena
usize
arena_free_space(const Arena *arena);

#ifdef ARENA_IMPLEMENTATION
#include "common.h"

struct Arena {
	usize size; // Total size of the arena
	usize used; // Amount of memory currently used
	u8 *memory; // Pointer to the allocated memory block
};

void *
arena_init(Arena *arena, const usize size) {
	arena->size = size;
	arena->used = 0;
	arena->memory = (u8 *)ARENA_MALLOC(size);
	if (!arena->memory) {
		return ARENA_NOT_INITIALIZED; // Allocation failed
	}
	return arena->memory;
}

void *
arena_alloc(Arena *arena, const usize size) {
	if (arena->used + size > arena->size) {
		return ARENA_NOT_ENOUGH_SPACE;
	}
	void *ptr = arena->memory + arena->used;
	arena->used += size;
	return ptr;
}

void
arena_free(Arena *arena) {
	if (arena->memory) {
		ARENA_FREE(arena->memory);
		arena->memory = NULL;
	}
	arena->size = 0;
	arena->used = 0;
}

void
arena_reset(Arena *old_arena) {
	old_arena->used = 0; // Reset used memory to zero
}

b8
arena_has_space(const Arena *arena, const usize size) {
	return (arena->used + size <= arena->size);
}

usize
arena_used(const Arena *arena) {
	return arena->used;
}

usize
arena_total_size(const Arena *arena) {
	return arena->size;
}

usize
arena_free_space(const Arena *arena) {
	return arena->size - arena->used;
}

#endif // ARENA_IMPLEMENTATION

#endif // ARENA_H
