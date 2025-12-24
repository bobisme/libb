// str.h - Non-owning string slice

#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "result.h"
#include "types.h"

// Forward declaration
typedef struct Arena Arena;

// Non-owning view into string data. NOT null-terminated.
typedef struct Str Str;
struct Str {
  const char *p;
  size_t n;
};

// Iterator of Str's
typedef struct StrSplitIter StrSplitIter;
struct StrSplitIter {
  Str str;
  char delim;
};

// Create Str from C string literal
#define str_lit(s) ((Str){.p = (s), .n = sizeof(s) - 1})

static inline Str str_new(const char *ptr, size_t len) {
  return (Str){.p = ptr, .n = len};
}

// Create Str from null-terminated C string
static inline Str str_from_cstr(const char *s) {
  return (Str){.p = s, .n = s ? strlen(s) : 0};
}

// Basic operations - inline for performance
static inline bool str_eq(Str a, Str b) {
  return a.n == b.n && (a.n == 0 || memcmp(a.p, b.p, a.n) == 0);
}

static inline Str str_slice(Str s, size_t off, size_t len) {
  if (off >= s.n)
    return (Str){.p = s.p + s.n, .n = 0};
  if (off + len > s.n)
    len = s.n - off;
  return (Str){.p = s.p + off, .n = len};
}

static inline bool str_starts_with(Str s, Str prefix) {
  return s.n >= prefix.n && memcmp(s.p, prefix.p, prefix.n) == 0;
}

static inline bool str_ends_with(Str s, Str suffix) {
  return s.n >= suffix.n &&
         memcmp(s.p + s.n - suffix.n, suffix.p, suffix.n) == 0;
}

Str str_trim(Str s);

StrSplitIter str_split(Str s, char delim);
bool str_iter_split_next(StrSplitIter *it, Str *out);

StrSplitIter str_split_lines(Str s);
char *str_to_cstr(Arena *a, Str s); // Null-terminated copy

DEFINE_RESULT(ToI64, i64, int);

ToI64 str_to_i64(Str s);

#endif // STR_H
