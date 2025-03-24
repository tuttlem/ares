
#include <kernel.h>
#include <drivers.h>
#include <device.h>
#include <idt.h>
#include <pit.h>
#include <time.h>
#include <cpuid.h>

extern void set_stdout_device(device_t* dev);

void main() {
  idt_init();
  drivers_init_all();

  device_t *con = device_find_by_name("console0");
  set_stdout_device(con);

  device_t *kbd = device_find_by_name("ps2kbd");

  while (1) {
    char ch;

    if (kbd->read(kbd, &ch, 1) == 1) {
        printf("%c", ch);
    }

    if (ch == 13) {
      u32 ticks = clock_seconds();
      printf("\n [%d] ", ticks);
      ch = 0;
    }
  }

  drivers_term_all();

  while (1);
}

