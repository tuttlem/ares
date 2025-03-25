#include "time.h"

extern uint64_t _ares_ticks;

uint64_t clock_ticks() {
  return _ares_ticks;
}

uint64_t clock_seconds() {
  return _ares_ticks / 100;
}
