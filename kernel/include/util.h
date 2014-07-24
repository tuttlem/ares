
/*
 * Ares 64-bit Operating System
 *
 * Interrupt setup module
 */

#ifndef __ares_util_h_

#define __ares_util_h_

#include <types.h>

static inline u64 farpeekq(u16 sel, void *off) {
  u64 ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline u32 farpeekd(u16 sel, void *off) {
  u32 ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline u16 farpeekw(u16 sel, void *off) {
  u16 ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline u8 farpeekb(u16 sel, void *off) {
  u8 ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline void farpokeq(u16 sel, void *off, u64 v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpoked(u16 sel, void *off, u32 v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpokew(u16 sel, void *off, u16 v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpokeb(u16 sel, void *off, u8 v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

#endif
