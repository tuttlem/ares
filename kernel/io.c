
#include <io.h>

/** Write a byte to a software port */
void outb(u16 port, u8 value) {
   asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/** Read a byte from a software port */
u8 inb(u16 port) {
   u8 val;
   asm volatile ("inb %1, %0" : "=a" (val) : "dN" (port));
   return val;
}

/** Read a short from a software port */
u16 inw(u16 port) {
   u16 val;
   asm volatile ("inw %1, %0" : "=a" (val) : "dN" (port));
}

