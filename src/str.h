// str.h - Non-owning string slice

#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

// Forward declaration
typedef struct Arena Arena;

// Non-owning view into string data. NOT null-terminated.
typedef struct Str Str;

struct Str {
  const char *p;
  size_t n;
};

// Create Str from C string literal
#define str_lit(s) ((Str){.p = (s), .n = sizeof(s) - 1})

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

// Functions requiring implementation
Str str_trim(Str s);
int64_t str_to_i64(Str s, bool *ok);
int64_t str_parse_i64(Str *s); // Parse and advance pointer

// Functions requiring arena
Str *str_split_lines(Arena *a, Str s, size_t *count);
Str *str_split(Arena *a, Str s, char delim, size_t *count);
char *str_to_cstr(Arena *a, Str s); // Null-terminated copy

#endif // STR_H
