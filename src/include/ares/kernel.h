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

#include <panic.h>

#define min(a, b) ((a > b) ? b : a)
#define max(a, b) ((a > b) ? a : b)
#define abs(a)    ((a >= 0) ? a : -a)

uint32_t rand();

#endif /* __ares_kernel_h_ */
