/*
 * Ares 64-bit Operating System
 *
 * Keyboard driver
 */

#include <types.h>
#include <io.h>
#include <interrupt.h>

#define KBD_DATA_PORT		0x60

/* The keyboard IRQ handler routine */
void kbd_drv_handler(struct _registers regs);

/* Initializes the keyboard driver */
int kbd_drv_init() {
  /* install an interrupt handler that will listen to IRQ1 which
     is the keyboard */
  interrupt_register_handler(IRQ1, kbd_drv_handler);
}

/* Unloads the keyboard driver */
int kbd_drv_term() {
  /* remove the keyboard handler */
  interrupt_register_handler(IRQ1, NULL);
}

/* The keyboard IRQ handler routine */
void kbd_drv_handler(struct _registers regs) {
  /* read the scan code from the keyboard - take note: this is not the
     ASCII code of the character */
  u8 code = inb(KBD_DATA_PORT);

  /* for debug sake */
  printf("kbd_drv: %d\n", code);
}
