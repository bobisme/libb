// types.h - Rust-style type aliases

#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <stdint.h>

// Unsigned integers
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Signed integers
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floats
typedef float f32;
typedef double f64;

// Pointer-sized
typedef size_t usize;
typedef ptrdiff_t isize;

#endif // TYPES_H
