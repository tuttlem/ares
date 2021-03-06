
#include <kernel.h>

/* Prints a message to the console, then infinitely spins */
void panic(const char *msg, const char *file, u32 line) {
   asm volatile ("cli");
   printf("PANIC: %s at %s:%d\n", msg, file, line);
   for (;;);
}

/* Prints an assertion message to the console, then infinitely spins */
void panic_assert(const char *file, u32 line, const char *desc) {
   asm volatile ("cli");
   printf("ASSERT-PANIC: %s at %s:%d\n", desc, file, line);
   for (;;);
}
