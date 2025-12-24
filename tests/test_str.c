// test_str.c - String tests

#include "../src/arena.h"
#include "../src/str.h"
#include "test.h"

TEST(str_lit_creates_correct_length) {
  Str s = str_lit("hello");
  ASSERT_EQ(s.n, 5);
  ASSERT(s.p[0] == 'h');
}

TEST(str_eq_matches_identical) {
  Str a = str_lit("hello");
  Str b = str_lit("hello");
  ASSERT(str_eq(a, b));
}

TEST(str_eq_rejects_different) {
  Str a = str_lit("hello");
  Str b = str_lit("world");
  ASSERT(!str_eq(a, b));
}

TEST(str_slice_extracts_substring) {
  Str s = str_lit("hello world");
  Str sub = str_slice(s, 6, 5);
  ASSERT(str_eq(sub, str_lit("world")));
}

TEST(str_starts_with_works) {
  Str s = str_lit("hello world");
  ASSERT(str_starts_with(s, str_lit("hello")));
  ASSERT(!str_starts_with(s, str_lit("world")));
}

TEST(str_ends_with_works) {
  Str s = str_lit("hello world");
  ASSERT(str_ends_with(s, str_lit("world")));
  ASSERT(!str_ends_with(s, str_lit("hello")));
}

int main(void) {
  printf("str tests:\n");
  RUN_TEST(str_lit_creates_correct_length);
  RUN_TEST(str_eq_matches_identical);
  RUN_TEST(str_eq_rejects_different);
  RUN_TEST(str_slice_extracts_substring);
  RUN_TEST(str_starts_with_works);
  RUN_TEST(str_ends_with_works);
  TEST_REPORT();
  return test_failed;
}
