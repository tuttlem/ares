
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

/* Read the current value of the CPU's time-stamp counter */
static inline u64 rdtsc() {
  u64 ret;
  asm volatile ("rdtsc" : "=A"(ret));
  return ret;
}

/* Read the value of cr1 */
static inline u64 get_cr1() {
  u64 ret;
  asm volatile ("mov %%cr1, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr2 */
static inline u64 get_cr2() {
  u64 ret;
  asm volatile ("mov %%cr2, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr3 */
static inline u64 get_cr3() {
  u64 ret;
  asm volatile ("mov %%cr3, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr4 */
static inline u64 get_cr4() {
  u64 ret;
  asm volatile ("mov %%cr4, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr0 */
static inline u64 get_cr0() {
  u64 ret;
  asm volatile ("mov %%cr0, %0" : "=r"(val));
  return ret;
}

/* Invalidate the TLB (Translation Lookaside Buffer) for one specific virtual address */
static inline void invlpg(void *m) {
  asm volatile ("invlpg (%0)" : : "m"(m) : "memory");
}

/* Write a 64-bit value to a MSR */
static inline void wrmsr(u32 id, u64 value) {
  asm volatile ("wrmsr" : : "c"(id), "A"(value));
}

/* Read a 64-bit value from a MSR */
static inline u64 rdmsr(u32 id) {
  u64 value;
  asm volatile ("rdmsr" : "=A"(value) : "c"(id));
  return value;
}

#endif
