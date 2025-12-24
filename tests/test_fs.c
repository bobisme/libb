#include <stdio.h>

#include "../src/arena.h"
#include "../src/fs.h"
#include "../src/str.h"

#include "test.h"

TEST(fs_read_file_works) {
  FILE *f = fopen("/tmp/libb_test.txt", "w");
  ASSERT(f != NULL);
  fprintf(f, "this is my test data");
  fclose(f);

  Arena a;
  arena_init(&a, 4096);

  auto res = fs_read_file(&a, "/tmp/libb_test.txt");
  ASSERT(res.ok == true);
  auto content = res.val;
  ASSERT(str_eq(content, str_lit("this is my test data")));

  arena_free(&a);
  remove("/tmp/libb_test.txt");
}

int main(void) {
  printf("fs tests:\n");
  RUN_TEST(fs_read_file_works);
  TEST_REPORT();
  return test_failed;
}
