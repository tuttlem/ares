
/**
 * Ares 64-bit operating system
 *
 * Software port I/O module
 */

#ifndef __ares_io_h_

#define __ares_io_h_

#include <types.h>

/** Write a byte to a software port */
static inline void outb(uint16_t port, uint8_t value) {
  asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

/** Read a byte from a software port */
static inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/** Read a short from a software port */
static inline uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

/** Forces the CPU to was for an I/O operation to complete */
static inline void io_wait() {
  asm volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif /* __ares_io_h_ */
