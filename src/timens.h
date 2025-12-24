#ifndef TIMENS_H
#define TIMENS_H

#include <time.h>

#include "types.h"

static inline u64 now_ns(void) {
  struct timespec ts;
  timespec_get(&ts, TIME_UTC);
  return (u64)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}
#endif // !TIMENS_H
