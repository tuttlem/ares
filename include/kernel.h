/**
 * Ares 64-bit operating system
 *
 * General kernel include
 */

#ifndef __ares_kernel_h_

#define __ares_kernel_h_

#include <types.h>

#define PANIC(msg)      panic(msg, __FILE__, __LINE__)
#define ASSERT(b)       ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

/* Print a kernel message */
void printf(const char *fmt, ...);

/* Panic prototypes */
extern void panic(const char *msg, const char *file, u32 line);
extern void panic_assert(const char *file, u32 line, const char *desc);

#endif /* __ares_kernel_h_ */
