// arena.h - Simple bump allocator

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct Arena Arena;

struct Arena {
  char *buf;
  size_t used;
  size_t cap;
};

// Initialize arena with given capacity (allocates from heap)
void arena_init(Arena *a, size_t cap);

// Allocate `size` bytes with `align` alignment
void *arena_alloc(Arena *a, size_t size, size_t align);

// Reset arena (keeps buffer, zeroes usage)
void arena_reset(Arena *a);

// Free arena's backing buffer
void arena_free(Arena *a);

// Convenience: alloc with default alignment
#define arena_push(a, T) ((T *)arena_alloc((a), sizeof(T), alignof(T)))
#define arena_push_array(a, T, n)                                              \
  ((T *)arena_alloc((a), sizeof(T) * (n), alignof(T)))

#endif // ARENA_H
