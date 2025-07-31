#ifndef ALLOCATOR_COMMON_H
#define ALLOCATOR_COMMON_H

#include "types.h"

typedef struct common_allocator {
	void *context;
	void *(*alloc)(void *context, usize size);
	void (*free)(void *context, void *ptr_or_size);
	void (*free_all)(void *context);
} allocator;

#endif // ALLOCATOR_COMMON_H
