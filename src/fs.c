// fs.c - Filesystem operations implementation

#include "fs.h"
#include "arena.h"
#include <stdio.h>

Str fs_read_file(Arena *a, const char *path) {
  // TODO: implement
  return (Str){.p = NULL, .n = 0};
}

int fs_exists(const char *path) {
  // TODO: implement
  return 0;
}
