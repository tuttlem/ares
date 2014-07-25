
#include <kernel.h>
#include <idt.h>
#include <cpuid.h>

void kbd_drv_init();
void kbd_drv_term();

void main() {
   idt_init();
kbd_drv_init();

/*   PANIC("Show's over, folks!"); */

   while (1);
}

