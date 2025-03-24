/**
 * Ares 64-bit operating system
 *
 * General kernel include
 */

#ifndef __ares_kernel_h_

#define __ares_kernel_h_

#include <types.h>
#include <ctype.h>
#include <spinlock.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PANIC(msg)      panic(msg, __FILE__, __LINE__)
#define ASSERT(b)       ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

#define min(a, b) ((a > b) ? b : a)
#define max(a, b) ((a > b) ? a : b)
#define abs(a)    ((a >= 0) ? a : -a)

/* Panic prototypes */
extern void panic(const char *msg, const char *file, u32 line);
extern void panic_assert(const char *file, u32 line, const char *desc);

u32 rand();

#endif /* __ares_kernel_h_ */
