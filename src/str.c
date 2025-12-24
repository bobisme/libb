// str.c - String operations implementation

#include <ctype.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "arena.h"
#include "result.h"
#include "str.h"
#include "types.h"

Str str_trim(Str s) {
  size_t i = 0;
  while (i < s.n && isspace((unsigned char)s.p[i]))
    i++;

  size_t j = s.n;
  while (j > i && isspace((unsigned char)s.p[j - 1]))
    j--;

  return str_slice(s, i, j - i);
}

ToI64 str_to_i64(Str s) {
  char buf[24]; // fits any i64
  size_t len = s.n < 23 ? s.n : 23;
  memcpy(buf, s.p, len);
  buf[len] = '\0';

  errno = 0;
  i64 n = strtoll(buf, NULL, 10);
  if (errno)
    return Err(ToI64, errno);
  return Ok(ToI64, n);
}

StrSplitIter str_split(Str s, char delim) {
  return (StrSplitIter){.delim = delim, .str = s};
}

StrSplitIter str_split_lines(Str s) { return str_split(s, '\n'); }

bool str_iter_split_next(StrSplitIter *it, Str *out) {
  if (it->str.p == NULL) {
    return false;
  }

  const char *end_ptr = memchr(it->str.p, it->delim, it->str.n);
  if (end_ptr == NULL) {
    // No more delims, return remaining
    *out = it->str;
    it->str.p = NULL;
    return true;
  }

  size_t n = (size_t)(end_ptr - it->str.p);
  *out = (Str){.p = it->str.p, .n = n};

  it->str.p = end_ptr + 1;
  it->str.n -= n + 1;
  return true;
}

char *str_to_cstr(Arena *a, Str s) {
  char *cstr_ptr = arena_alloc(a, s.n + 1, 1);
  memcpy(cstr_ptr, s.p, s.n);
  cstr_ptr[s.n] = '\0';
  return cstr_ptr;
}
