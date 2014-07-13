
/**
 * Ares 64-bit operating system
 *
 * Software port I/O module
 */

#ifndef __ares_io_h_

#define __ares_io_h_

#include "types.h"

/** Write a byte to a software port */
void outb(u16 port, u8 value);

/** Read a byte from a software port */
u8 inb(u16 port);

/** Read a short from a software port */
u16 inw(u16 port);


#endif /* __ares_io_h_ */
