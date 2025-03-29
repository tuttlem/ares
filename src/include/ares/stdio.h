
#ifndef __ares_stdio_h

#define __ares_stdio_h

#include <stdarg.h>

/* Print a kernel message */
void printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list ap);

#endif