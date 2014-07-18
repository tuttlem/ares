
#include <kernel.h>
#include <idt.h>
#include <cpuid.h>

u32 tick = 0;

void test_handler(struct _registers regs) {
   printf("Tick: %d\n", tick);
   tick ++;
}

void main() {
   idt_init();
   interrupt_register_handler(IRQ0, &test_handler);
   pit_init(50);


   while (1);
}

