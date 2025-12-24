// fs.c - Filesystem operations implementation

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "arena.h"
#include "fs.h"
#include "result.h"

FReadResult fs_read_file(Arena *a, const char *path) {
  struct stat s;
  if (stat(path, &s) != 0) {
    return Err(FReadResult, FileStatFailed);
  }

  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    return Err(FReadResult, FileOpenFailed);
  }

  size_t size = s.st_size;
  char *buf = arena_alloc(a, size, 1);
  auto n_read = fread(buf, 1, size, fp);
  fclose(fp);

  if (n_read != size) {
    return Err(FReadResult, FileReadFailed);
  }

  return Ok(FReadResult, str_new(buf, size));
}

bool fs_exists(const char *path) {
  struct stat s;
  return stat(path, &s) == 0;
}
