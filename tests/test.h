// test.h - Minimal test framework
//
// Usage:
//   TEST(my_test_name) {
//       ASSERT(1 + 1 == 2);
//       ASSERT_EQ(42, 42);
//       ASSERT_STR_EQ("hello", "hello");
//   }
//
//   int main(void) {
//       RUN_TEST(my_test_name);
//       TEST_REPORT();
//       return test_failed;
//   }

#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

static int test_passed = 0;
static int test_failed = 0;
static const char *current_test = NULL;

#define TEST(name) static void test_##name(void)

#define RUN_TEST(name)                                                         \
  do {                                                                         \
    current_test = #name;                                                      \
    test_##name();                                                             \
    if (current_test) {                                                        \
      test_passed++;                                                           \
      printf("  PASS: %s\n", #name);                                           \
    }                                                                          \
  } while (0)

#define FAIL(msg)                                                              \
  do {                                                                         \
    printf("  FAIL: %s\n", current_test);                                      \
    printf("        %s:%d: %s\n", __FILE__, __LINE__, msg);                    \
    test_failed++;                                                             \
    current_test = NULL;                                                       \
    return;                                                                    \
  } while (0)

#define ASSERT(expr)                                                           \
  do {                                                                         \
    if (!(expr)) {                                                             \
      FAIL(#expr);                                                             \
    }                                                                          \
  } while (0)

#define ASSERT_EQ(a, b)                                                        \
  do {                                                                         \
    if ((a) != (b)) {                                                          \
      printf("  FAIL: %s\n", current_test);                                    \
      printf(                                                                  \
          "        %s:%d: %lld != %lld\n", __FILE__, __LINE__, (long long)(a), \
          (long long)(b)                                                       \
      );                                                                       \
      test_failed++;                                                           \
      current_test = NULL;                                                     \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define ASSERT_STR_EQ(a, b)                                                    \
  do {                                                                         \
    if (strcmp((a), (b)) != 0) {                                               \
      printf("  FAIL: %s\n", current_test);                                    \
      printf(                                                                  \
          "        %s:%d: \"%s\" != \"%s\"\n", __FILE__, __LINE__, (a), (b)    \
      );                                                                       \
      test_failed++;                                                           \
      current_test = NULL;                                                     \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define TEST_REPORT()                                                          \
  do {                                                                         \
    printf("\n%d passed, %d failed\n", test_passed, test_failed);              \
  } while (0)

#endif // TEST_H
