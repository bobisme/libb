// arena.c - Simple bump allocator implementation

#include "arena.h"
#include <stdlib.h>
#include <string.h>

void arena_init(Arena *a, size_t cap) {
  a->buf = malloc(cap);
  a->cap = cap;
  a->used = 0;
}

void *arena_alloc(Arena *a, size_t size, size_t align) {
  size_t aligned = (a->used + align - 1) & ~(align - 1);
  if ((aligned + size) > a->cap)
    return NULL;

  void *ptr = &a->buf[aligned];
  a->used = aligned + size;

  return ptr;
}

void arena_reset(Arena *a) { a->used = 0; }

void arena_free(Arena *a) { free(a->buf); }
