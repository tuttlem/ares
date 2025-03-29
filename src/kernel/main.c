
#include <kernel.h>
#include <log.h>
#include <heap.h>
#include <drivers.h>
#include <device.h>
#include <idt.h>
#include <pit.h>
#include <time.h>
#include <cpuid.h>
#include <vmm.h>

#define KHEAP_START 0x1000000
#define KHEAP_END   0x1020000

extern void set_stdout_device(device_t* dev);
extern void _ares_page_fault_handler(struct _registers regs);

void main() {
  idt_init();
  interrupt_register_handler(14, _ares_page_fault_handler);
  kheap_init((void*)KHEAP_START, (void*)KHEAP_END);
  drivers_register_static();
  drivers_init_all();

  device_t *con = device_find_by_name("console0");
  set_stdout_device(con);

  log_set_level(LOG_LEVEL_DEBUG);
  log_info("Starting Ares ...");

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

