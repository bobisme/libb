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

TEST(str_split_basic) {
  Str s = str_lit("a,b,c");
  StrSplitIter it = str_split(s, ',');
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("a")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("b")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("c")));

  ASSERT(!str_iter_split_next(&it, &out)); // done
}

TEST(str_split_empty_segments) {
  Str s = str_lit("a,,b");
  StrSplitIter it = str_split(s, ',');
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("a")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT_EQ(out.n, 0); // empty segment

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("b")));

  ASSERT(!str_iter_split_next(&it, &out));
}

TEST(str_split_no_delimiter) {
  Str s = str_lit("hello");
  StrSplitIter it = str_split(s, ',');
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("hello")));

  ASSERT(!str_iter_split_next(&it, &out));
}

TEST(str_split_empty_string) {
  Str s = str_lit("");
  StrSplitIter it = str_split(s, ',');
  Str out;

  // Empty string should yield one empty segment
  ASSERT(str_iter_split_next(&it, &out));
  ASSERT_EQ(out.n, 0);

  ASSERT(!str_iter_split_next(&it, &out));
}

TEST(str_split_trailing_delimiter) {
  Str s = str_lit("a,b,");
  StrSplitIter it = str_split(s, ',');
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("a")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("b")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT_EQ(out.n, 0); // trailing empty

  ASSERT(!str_iter_split_next(&it, &out));
}

TEST(str_split_leading_delimiter) {
  Str s = str_lit(",a");
  StrSplitIter it = str_split(s, ',');
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT_EQ(out.n, 0); // leading empty

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("a")));

  ASSERT(!str_iter_split_next(&it, &out));
}

// --- str_trim tests ---

TEST(str_trim_removes_leading_whitespace) {
  Str s = str_lit("   hello");
  Str t = str_trim(s);
  ASSERT(str_eq(t, str_lit("hello")));
}

TEST(str_trim_removes_trailing_whitespace) {
  Str s = str_lit("hello   ");
  Str t = str_trim(s);
  ASSERT(str_eq(t, str_lit("hello")));
}

TEST(str_trim_removes_both) {
  Str s = str_lit("  hello world  ");
  Str t = str_trim(s);
  ASSERT(str_eq(t, str_lit("hello world")));
}

TEST(str_trim_handles_tabs_newlines) {
  Str s = str_lit("\t\n hello \n\t");
  Str t = str_trim(s);
  ASSERT(str_eq(t, str_lit("hello")));
}

TEST(str_trim_all_whitespace) {
  Str s = str_lit("   \t\n  ");
  Str t = str_trim(s);
  ASSERT_EQ(t.n, 0);
}

TEST(str_trim_empty_string) {
  Str s = str_lit("");
  Str t = str_trim(s);
  ASSERT_EQ(t.n, 0);
}

TEST(str_trim_no_whitespace) {
  Str s = str_lit("hello");
  Str t = str_trim(s);
  ASSERT(str_eq(t, str_lit("hello")));
}

// --- str_to_i64 tests ---

TEST(str_to_i64_parses_positive) {
  Str s = str_lit("42");
  ToI64 r = str_to_i64(s);
  ASSERT(r.ok);
  ASSERT_EQ(r.val, 42);
}

TEST(str_to_i64_parses_negative) {
  Str s = str_lit("-123");
  ToI64 r = str_to_i64(s);
  ASSERT(r.ok);
  ASSERT_EQ(r.val, -123);
}

TEST(str_to_i64_parses_zero) {
  Str s = str_lit("0");
  ToI64 r = str_to_i64(s);
  ASSERT(r.ok);
  ASSERT_EQ(r.val, 0);
}

TEST(str_to_i64_stops_at_non_digit) {
  // "123abc" should parse 123 (strtol behavior)
  Str s = str_lit("123abc");
  ToI64 r = str_to_i64(s);
  ASSERT(r.ok);
  ASSERT_EQ(r.val, 123);
}

TEST(str_to_i64_handles_leading_whitespace) {
  Str s = str_lit("  42");
  ToI64 r = str_to_i64(s);
  ASSERT(r.ok);
  ASSERT_EQ(r.val, 42);
}

// --- str_to_cstr tests ---

TEST(str_to_cstr_null_terminates) {
  Arena a;
  arena_init(&a, 4096);

  Str s = str_lit("hello");
  char *cstr = str_to_cstr(&a, s);

  ASSERT_STR_EQ(cstr, "hello");
  ASSERT_EQ(cstr[5], '\0');

  arena_free(&a);
}

TEST(str_to_cstr_empty_string) {
  Arena a;
  arena_init(&a, 4096);

  Str s = str_lit("");
  char *cstr = str_to_cstr(&a, s);

  ASSERT_STR_EQ(cstr, "");
  ASSERT_EQ(cstr[0], '\0');

  arena_free(&a);
}

TEST(str_to_cstr_preserves_content) {
  Arena a;
  arena_init(&a, 4096);

  Str s = str_lit("hello world");
  char *cstr = str_to_cstr(&a, s);

  ASSERT_EQ(strlen(cstr), 11);
  ASSERT_STR_EQ(cstr, "hello world");

  arena_free(&a);
}

// --- str_split_lines tests ---

TEST(str_split_lines_basic) {
  Str s = str_lit("line1\nline2\nline3");
  StrSplitIter it = str_split_lines(s);
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("line1")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("line2")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("line3")));

  ASSERT(!str_iter_split_next(&it, &out));
}

TEST(str_split_lines_trailing_newline) {
  Str s = str_lit("line1\nline2\n");
  StrSplitIter it = str_split_lines(s);
  Str out;

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("line1")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT(str_eq(out, str_lit("line2")));

  ASSERT(str_iter_split_next(&it, &out));
  ASSERT_EQ(out.n, 0); // trailing empty

  ASSERT(!str_iter_split_next(&it, &out));
}

int main(void) {
  printf("str tests:\n");
  RUN_TEST(str_lit_creates_correct_length);
  RUN_TEST(str_eq_matches_identical);
  RUN_TEST(str_eq_rejects_different);
  RUN_TEST(str_slice_extracts_substring);
  RUN_TEST(str_starts_with_works);
  RUN_TEST(str_ends_with_works);
  RUN_TEST(str_split_basic);
  RUN_TEST(str_split_empty_segments);
  RUN_TEST(str_split_no_delimiter);
  RUN_TEST(str_split_empty_string);
  RUN_TEST(str_split_trailing_delimiter);
  RUN_TEST(str_split_leading_delimiter);
  // trim tests
  RUN_TEST(str_trim_removes_leading_whitespace);
  RUN_TEST(str_trim_removes_trailing_whitespace);
  RUN_TEST(str_trim_removes_both);
  RUN_TEST(str_trim_handles_tabs_newlines);
  RUN_TEST(str_trim_all_whitespace);
  RUN_TEST(str_trim_empty_string);
  RUN_TEST(str_trim_no_whitespace);
  // str_to_i64 tests
  RUN_TEST(str_to_i64_parses_positive);
  RUN_TEST(str_to_i64_parses_negative);
  RUN_TEST(str_to_i64_parses_zero);
  RUN_TEST(str_to_i64_stops_at_non_digit);
  RUN_TEST(str_to_i64_handles_leading_whitespace);
  // str_to_cstr tests
  RUN_TEST(str_to_cstr_null_terminates);
  RUN_TEST(str_to_cstr_empty_string);
  RUN_TEST(str_to_cstr_preserves_content);
  // str_split_lines tests
  RUN_TEST(str_split_lines_basic);
  RUN_TEST(str_split_lines_trailing_newline);
  TEST_REPORT();
  return test_failed;
}
