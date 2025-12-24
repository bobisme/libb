#include "vec.h"
#include "arena.h"

void vec_grow_(
    Arena *a, void **ptr, size_t *cap, size_t elem_size, size_t align
) {
  size_t new_cap = *cap * 2;
  void *new_ptr = arena_alloc(a, new_cap, align);
  memcpy(new_ptr, *ptr, *cap * elem_size);
  *ptr = new_ptr;
  *cap = new_cap;
}
