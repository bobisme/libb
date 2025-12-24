// fs.h - Filesystem operations

#ifndef FS_H
#define FS_H

#include "result.h"
#include "str.h"

// Forward declaration
typedef struct Arena Arena;

enum FileErrorCode {
  FileOpenFailed,
  FileReadFailed,
  FileDoesNotExist,
  FileStatFailed,
};

DEFINE_RESULT(FReadResult, Str, enum FileErrorCode);

// Read entire file into arena, return as Str
FReadResult fs_read_file(Arena *a, const char *path);

// Check if file exists
bool fs_exists(const char *path);

#endif // FS_H
