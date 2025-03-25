
/*
 * Ares 64-bit Operating System
 *
 * Interrupt setup module
 */

#ifndef __ares_util_h_

#define __ares_util_h_

#include <types.h>

static inline uint64_t farpeekq(uint16_t sel, void *off) {
  uint64_t ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline uint32_t farpeekd(uint16_t sel, void *off) {
  uint32_t ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline uint16_t farpeekw(uint16_t sel, void *off) {
  uint16_t ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline uint8_t farpeekb(uint16_t sel, void *off) {
  uint8_t ret;
  asm ("push %%fs\n\t"
       "mov  %1, %%fs\n\t"
       "mov  %%fs:(%2), %0\n\t"
       "pop  %%fs"
       : "=r"(ret)
       : "g"(sel), "r"(off));
  return ret;
}

static inline void farpokeq(uint16_t sel, void *off, uint64_t v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpoked(uint16_t sel, void *off, uint32_t v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpokew(uint16_t sel, void *off, uint16_t v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

static inline void farpokeb(uint16_t sel, void *off, uint8_t v) {
  asm ("push %%fs\n\t"
       "mov  %0, %%fs\n\t"
       "mov  %2, %%fs:(%1)\n\t"
       "pop  %%fs\n\t"
       :
       : "g"(sel), "r"(off), "r"(v));
}

/* Read the current value of the CPU's time-stamp counter */
static inline uint64_t rdtsc() {
  uint64_t ret;
  asm volatile ("rdtsc" : "=A"(ret));
  return ret;
}

/* Read the value of cr1 */
static inline uint64_t get_cr1() {
  uint64_t ret;
  asm volatile ("mov %%cr1, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr2 */
static inline uint64_t get_cr2() {
  uint64_t ret;
  asm volatile ("mov %%cr2, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr3 */
static inline uint64_t get_cr3() {
  uint64_t ret;
  asm volatile ("mov %%cr3, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr4 */
static inline uint64_t get_cr4() {
  uint64_t ret;
  asm volatile ("mov %%cr4, %0" : "=r"(val));
  return ret;
}

/* Read the value of cr0 */
static inline uint64_t get_cr0() {
  uint64_t ret;
  asm volatile ("mov %%cr0, %0" : "=r"(val));
  return ret;
}

/* Invalidate the TLB (Translation Lookaside Buffer) for one specific virtual address */
static inline void invlpg(void *m) {
  asm volatile ("invlpg (%0)" : : "m"(m) : "memory");
}

/* Write a 64-bit value to a MSR */
static inline void wrmsr(uint32_t id, uint64_t value) {
  asm volatile ("wrmsr" : : "c"(id), "A"(value));
}

/* Read a 64-bit value from a MSR */
static inline uint64_t rdmsr(uint32_t id) {
  uint64_t value;
  asm volatile ("rdmsr" : "=A"(value) : "c"(id));
  return value;
}

#endif
