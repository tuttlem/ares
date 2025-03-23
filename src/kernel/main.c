
#include <kernel.h>
#include <drivers.h>
#include <device.h>
#include <idt.h>
#include <cpuid.h>

#include "../drivers/include/io.h"


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
  }

  drivers_term_all();

  while (1);
}

