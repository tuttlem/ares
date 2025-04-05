
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
#include <multiboot2.h>
#include <pmm.h>

#define KHEAP_START 0x1000000
#define KHEAP_END   0x1020000

extern void set_stdout_device(device_t* dev);
extern void _ares_page_fault_handler(struct _registers regs);

extern char* _ares_mb2_loader_name;
extern char* _ares_mb2_cmdline;

extern struct multiboot_tag_basic_meminfo* _ares_mb2_basic_meminfo;
extern struct multiboot_tag_bootdev*       _ares_mb2_bootdev;
extern struct multiboot_tag_mmap*      	   _ares_mb2_memmap;
extern struct multiboot_framebuffer*       _ares_mb2_framebuffer;

void kmain(uint64_t mb2_info_addr, uint32_t magic) {
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


  mb2_parse(mb2_info_addr, magic);
  vmm_unmap_zero_page();

  // pmm_init_from_mb2(); // <<<<------ triple fault!

  printf("Bootloader: \t%s\n", _ares_mb2_loader_name);
  printf("Command Line: \t%s\n", _ares_mb2_cmdline);

  printf("Basic Meminfo: \t%p\n", _ares_mb2_basic_meminfo);
  printf("Bootdev: \t%p\n", _ares_mb2_bootdev);
  printf("mmap: \t\t%p\n", _ares_mb2_memmap);
  printf("Framebuffer: \t%p\n", _ares_mb2_framebuffer);

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

