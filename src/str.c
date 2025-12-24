// str.c - String operations implementation

#include "str.h"
#include "arena.h"

Str str_trim(Str s) {
  // TODO: implement
  return s;
}

int64_t str_to_i64(Str s, bool *ok) {
  // TODO: implement
  if (ok)
    *ok = false;
  return 0;
}

int64_t str_parse_i64(Str *s) {
  // TODO: implement - parse int and advance s->p, shrink s->n
  return 0;
}

Str *str_split_lines(Arena *a, Str s, size_t *count) {
  // TODO: implement
  *count = 0;
  return NULL;
}

Str *str_split(Arena *a, Str s, char delim, size_t *count) {
  // TODO: implement
  *count = 0;
  return NULL;
}

char *str_to_cstr(Arena *a, Str s) {
  // TODO: implement
  return NULL;
}
