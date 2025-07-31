#ifndef ARENA_H
#define ARENA_H

#include "types.h"

// Defining ARENA memory allocator
#define ARENA_MALLOC malloc
#define ARENA_FREE free
#define ARENA_REALLLOC realloc
#define ARENA_MEMCPY memcpy

// Arena memory allocator
typedef struct Arena Arena;

// Initializes the arena with a specified size
void
arena_init(Arena *arena, usize size);

// Allocates a block of memory from the arena
void *
arena_alloc(Arena *arena, usize size);

// Frees the arena and its memory block
void
arena_free(Arena *arena);

// Resets the arena, freeing all allocated memory but keeping the arena
// structure intact
void
arena_reset(Arena *arena);

// Checks if the arena has enough memory to allocate a block of the specified
// size
b8
arena_has_space(const Arena *arena, usize size);

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
arena_init(Arena *arena, usize size) {
	arena->size = size;
	arena->used = 0;
	arena->memory = (u8 *)ARENA_MALLOC(size);
	if (!arena->memory) {
		return NULL; // Allocation failed
	}
	return arena->memory;
}

#endif // ARENA_IMPLEMENTATION

#endif // ARENA_H
