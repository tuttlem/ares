/**
 * Ares 64-bit operating system
 *
 * Programmable interval timer module
 */

#ifndef __ares_pit_h_

#define __ares_pit_h_

#include <types.h>
#include <interrupt.h>

#define PIT_CLOCK_OSC		1193182

/* Initialize the timer to run at a frequency */
void pit_init(u32 freq);

#endif