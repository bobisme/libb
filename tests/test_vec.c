// test_vec.c - Vector tests

#include "../src/arena.h"
#include "../src/vec.h"
#include "test.h"

TEST(vec_push_increments_length) {
  Arena a;
  arena_init(&a, 4096);

  Vec(int) v;
  vec_init(&v, &a, 8);

  ASSERT_EQ(v.n, 0);
  vec_push(&v, 42);
  ASSERT_EQ(v.n, 1);
  ASSERT_EQ(v.p[0], 42);

  arena_free(&a);
}

TEST(vec_push_multiple_values) {
  Arena a;
  arena_init(&a, 4096);

  Vec(int) v;
  vec_init(&v, &a, 8);

  for (int i = 0; i < 5; i++) {
    vec_push(&v, i * 10);
  }

  ASSERT_EQ(v.n, 5);
  ASSERT_EQ(v.p[0], 0);
  ASSERT_EQ(v.p[4], 40);

  arena_free(&a);
}

TEST(vec_pop_decrements_length) {
  Arena a;
  arena_init(&a, 4096);

  Vec(int) v;
  vec_init(&v, &a, 8);

  vec_push(&v, 1);
  vec_push(&v, 2);
  vec_push(&v, 3);

  int x = vec_pop(&v);
  ASSERT_EQ(x, 3);
  ASSERT_EQ(v.n, 2);

  arena_free(&a);
}

TEST(vec_clear_zeroes_length) {
  Arena a;
  arena_init(&a, 4096);

  Vec(int) v;
  vec_init(&v, &a, 8);

  vec_push(&v, 1);
  vec_push(&v, 2);
  vec_clear(&v);

  ASSERT_EQ(v.n, 0);

  arena_free(&a);
}

int main(void) {
  printf("vec tests:\n");
  RUN_TEST(vec_push_increments_length);
  RUN_TEST(vec_push_multiple_values);
  RUN_TEST(vec_pop_decrements_length);
  RUN_TEST(vec_clear_zeroes_length);
  TEST_REPORT();
  return test_failed;
}
