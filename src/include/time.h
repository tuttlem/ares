/**
* Ares 64-bit operating system
 *
 * Internal time management
 */

#ifndef __ares_time_h_

#define __ares_time_h_

#include <types.h>
#include <interrupt.h>

u64 clock_ticks(void);
u64 clock_seconds(void);

#endif