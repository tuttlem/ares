
#include <kernel.h>

uint32_t rand() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;

  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}
