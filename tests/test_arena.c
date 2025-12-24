// test_arena.c - Arena allocator tests

#include "../src/arena.h"
#include "test.h"

TEST(arena_init_creates_buffer) {
  Arena a;
  arena_init(&a, 1024);
  ASSERT(a.buf != NULL);
  ASSERT_EQ(a.cap, 1024);
  ASSERT_EQ(a.used, 0);
  arena_free(&a);
}

TEST(arena_alloc_returns_aligned_pointer) {
  Arena a;
  arena_init(&a, 1024);

  int *x = arena_push(&a, int);
  ASSERT(x != NULL);
  ASSERT(((size_t)x % _Alignof(int)) == 0);

  arena_free(&a);
}

TEST(arena_reset_zeroes_usage) {
  Arena a;
  arena_init(&a, 1024);

  arena_alloc(&a, 100, 1);
  ASSERT(a.used > 0);

  arena_reset(&a);
  ASSERT_EQ(a.used, 0);

  arena_free(&a);
}

int main(void) {
  printf("arena tests:\n");
  RUN_TEST(arena_init_creates_buffer);
  RUN_TEST(arena_alloc_returns_aligned_pointer);
  RUN_TEST(arena_reset_zeroes_usage);
  TEST_REPORT();
  return test_failed;
}
