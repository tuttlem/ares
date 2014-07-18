
/*
 * Ares 64-bit Operating System
 *
 * Interrupt setup module
 */

#ifndef __ares_idt_h_

#define __ares_idt_h_

#include <types.h>
#include <kernel.h>
#include <interrupt.h>
#include <string.h>

struct _idt_entry {
   u16   low_off;    /* offset bits 15..0 */
   u16   sel;        /* selector */
   u8    zero0;      /* zeroed out */
   u8    flags;      /* flag information */
   u16   mid_off;    /* offset bits 31..16 */
   u32   hi_off;     /* offset bits 63..32 */
   u32   zero1;      /* zeroed out */
} __attribute__((packed));

struct _idt {
   u16   limit;      /* length of the table */
   u64   base;       /* base address */
} __attribute__((packed));

/* Initializes the idt */
void idt_init();

#endif
