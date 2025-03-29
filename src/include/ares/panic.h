/**
 * Ares 64-bit operating system
 *
 * Kernel panic
 */

#ifndef __ares_panic_h_

#define __ares_panic_h_

#define PANIC(msg)      panic(msg, __FILE__, __LINE__)
#define ASSERT(b)       ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *msg, const char *file, uint32_t line);
extern void panic_assert(const char *file, uint32_t line, const char *desc);

#endif /* __ares_panic_h_ */
