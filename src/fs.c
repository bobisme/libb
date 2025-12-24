// fs.c - Filesystem operations implementation

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "arena.h"
#include "fs.h"
#include "result.h"
#include "types.h"

FReadResult fs_read_file(Arena *a, const char *path) {
  struct stat s;
  int stat_res = stat(path, &s);
  if (stat_res != 0) {
    return (FReadResult){.err = FileStatFailed};
  }

  size_t size = s.st_size;

  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    if (!fs_exists(path)) {
      return Err(FReadResult, FileStatFailed);
    }
    return Err(FReadResult, FileOpenFailed);
  }

  auto buf = arena_alloc(a, size, 4096);
  auto n_read = fread(buf, sizeof(u8), s.st_size, fp);
  if (n_read != size) {
    return Err(FReadResult, FileReadFailed);
  }

  auto str = (Str){.p = buf, .n = size};
  return Ok(FReadResult, str);
}

bool fs_exists(const char *path) {
  struct stat s;
  return stat(path, &s) == 0;
}
