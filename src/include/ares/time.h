/**
* Ares 64-bit operating system
 *
 * Internal time management
 */

#ifndef __ares_time_h_

#define __ares_time_h_

#include <types.h>
#include <interrupt.h>

uint64_t clock_ticks(void);
uint64_t clock_seconds(void);

#endif