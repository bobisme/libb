// vec.h - Generic dynamic array (header-only)
//
// Usage:
//   Vec(int) nums;
//   vec_init(&nums, &arena, 16);
//   vec_push(&nums, 42);
//   for (size_t i = 0; i < nums.n; i++) { ... nums.p[i] ... }

#ifndef VEC_H
#define VEC_H

#include "arena.h"
#include <stddef.h>
#include <string.h>

// Declare a vector type for element type T
#define Vec(T)                                                                 \
  struct {                                                                     \
    T *p;                                                                      \
    size_t n, cap;                                                             \
    Arena *a;                                                                  \
  }

// Initialize vector with arena and initial capacity
#define vec_init(v, arena, init_cap)                                           \
  do {                                                                         \
    (v)->a = (arena);                                                          \
    (v)->n = 0;                                                                \
    (v)->cap = (init_cap);                                                     \
    (v)->p = arena_alloc(                                                      \
        (arena), sizeof(*(v)->p) * (init_cap), alignof(typeof(*(v)->p))        \
    );                                                                         \
  } while (0)

// Push element onto vector
#define vec_push(v, val)                                                       \
  do {                                                                         \
    if ((v)->n >= (v)->cap) {                                                  \
      vec_grow_(                                                               \
          (v)->a, (void **)&(v)->p, &(v)->cap, sizeof(*(v)->p),                \
          alignof(typeof(*(v)->p))                                             \
      );                                                                       \
    }                                                                          \
    (v)->p[(v)->n++] = (val);                                                  \
  } while (0)

// Pop element from vector (undefined if empty)
#define vec_pop(v) ((v)->p[--(v)->n])

// Clear vector (keeps capacity)
#define vec_clear(v) ((v)->n = 0)

// Last element
#define vec_last(v) ((v)->p[(v)->n - 1])

// Internal grow function - implemented in arena.c or vec.c
void vec_grow_(
    Arena *a, void **ptr, size_t *cap, size_t elem_size, size_t align
);

#endif // VEC_H
