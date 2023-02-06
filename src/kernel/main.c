
#include <kernel.h>
#include <idt.h>
#include <cpuid.h>

void kbd_drv_init();
void kbd_drv_term();
u8 kbd_get_key();

u32 lock = 0;

void main() {
  idt_init();

  printf("Attempting lock: %d\n", lock);
  spin_lock(&lock);
  printf("Got the lock: %d\n", lock);
  spin_unlock(&lock);
  printf("Released the lock: %d\n", lock);

  kbd_drv_init();

  while (1) {
    u8 ch;

    if ((ch = kbd_get_key()) != 0x00) {
        printf("%c", ch);
    }
  }

  /*   PANIC("Show's over, folks!"); */

  while (1);
}

