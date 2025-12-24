// fs.h - Filesystem operations

#ifndef FS_H
#define FS_H

#include "str.h"

// Forward declaration
typedef struct Arena Arena;

// Read entire file into arena, return as Str
Str fs_read_file(Arena *a, const char *path);

// Check if file exists
int fs_exists(const char *path);

#endif // FS_H
