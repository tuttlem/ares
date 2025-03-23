
/**
 * Ares 64-bit operating system
 *
 * I/O Device Driver
 */

#ifndef __ares_drivers_io_h_

#define __ares_drivers_io_h_

#include <device.h>

/**
 * Sets the device driver for STDOUT
 */
void set_stdout_device(device_t* dev);

/**
 * Write a string to STDOUT
 */
int write_stdout(const char* buf, int len);

/**
 * Writes a single character to stdout
 */
int write_stdout_char(char ch, int len);

#endif /* __ares_drivers_io_h_ */
