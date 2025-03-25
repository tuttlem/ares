
#include <kernel.h>
#include <heap.h>
#include <drivers.h>
#include <device.h>
#include <idt.h>
#include <pit.h>
#include <time.h>
#include <cpuid.h>

#define KHEAP_START 0x1000000
#define KHEAP_END   0x1020000

extern void set_stdout_device(device_t* dev);

void main() {
  idt_init();
  kheap_init((void*)KHEAP_START, (void*)KHEAP_END);
  drivers_register_static();
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
      uint32_t ticks = clock_seconds();
      printf("\n [%d] ", ticks);
      ch = 0;
    }
  }

  drivers_term_all();

  while (1);
}

