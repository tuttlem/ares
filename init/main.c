
#include <kernel.h>
#include <idt.h>
#include <cpuid.h>

void main() {
   idt_init();
   PANIC("Show's over, folks!");

   while (1);
}

