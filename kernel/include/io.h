
/**
 * Ares 64-bit operating system
 *
 * Software port I/O module
 */

#ifndef __ares_io_h_

#define __ares_io_h_

#include <types.h>

/** Write a byte to a software port */
static inline void outb(u16 port, u8 value) {
  asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/** Read a byte from a software port */
static inline u8 inb(u16 port) {
  u8 ret;
  asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/** Read a short from a software port */
static inline u16 inw(u16 port) {
  u16 ret;
  asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/** Forces the CPU to was for an I/O operation to complete */
static inline void io_wait() {
  asm volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif /* __ares_io_h_ */
