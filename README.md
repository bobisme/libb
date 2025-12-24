# libb

Bob's personal C library.

Building this to refresh my C knowledge and to use for Advent of Code.

## Features

- **Arena allocator** - simple bump allocator, no per-object frees
- **Str** - non-owning string slices
- **Vec** - generic dynamic arrays (arena-backed)
- **fs** - file reading utilities

## Usage

```c
#include "libb.h"

int main(void) {
    Arena a;
    arena_init(&a, 1024 * 1024);  // 1MB

    Str input = fs_read_file(&a, "input.txt");
    size_t count;
    Str *lines = str_split_lines(&a, input, &count);

    Vec(i64) nums;
    vec_init(&nums, &a, 16);

    for (size_t i = 0; i < count; i++) {
        bool ok;
        vec_push(&nums, str_to_i64(lines[i], &ok));
    }

    arena_free(&a);
}
```

## Build

```shell
make        # build library
make test   # run tests
make clean  # remove build artifacts
```

## Requirements

- clang with C23 support
- POSIX environment
