
/**
 * Ares 64-bit operating system
 *
 * Console access module
 */

#ifndef __ares_console_h_

#define __ares_console_h_

#include <types.h>
#include <io.h>

/* Writes a character onto the console */
void console_put(char c);

/* Clears the console */
void console_clear();

/* Prints a string of text to the console */
void console_puts(const char *s);

#endif /* __ares_console_h_ */
