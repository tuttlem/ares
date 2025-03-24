#include "time.h"

extern u64 _ares_ticks;

u64 clock_ticks() {
  return _ares_ticks;
}

u64 clock_seconds() {
  return _ares_ticks / 100;
}
