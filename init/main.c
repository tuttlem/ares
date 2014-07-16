
#include <kernel.h>
#include <idt.h>

void main() {
   idt_init();
   printf("Made it back to main\n");

   asm volatile ("int $0x3");
   asm volatile ("int $0x4");

   while (1);
}

