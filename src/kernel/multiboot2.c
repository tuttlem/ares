
#include "multiboot2.h"
#include <stdio.h>
#include <stddef.h>

char* _ares_mb2_cmdline = NULL;
char* _ares_mb2_loader_name = NULL;

struct multiboot_tag_basic_meminfo* _ares_mb2_basic_meminfo = NULL;
struct multiboot_tag_bootdev*       _ares_mb2_bootdev = NULL;
struct multiboot_tag_mmap*      	_ares_mb2_memmap = NULL;
struct multiboot_framebuffer*       _ares_mb2_framebuffer = NULL;

void mb2_parse(uint64_t addr, uint32_t magic) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("multiboot2: bad magic number %d (expected 0x%08x)\n", magic, MULTIBOOT2_BOOTLOADER_MAGIC);
        return;
    }

    if (addr & 7) {
        printf("multiboot2: misaligned mbi 0x%016llx\n", addr);
        return;
    }

    uint64_t size = *(uint64_t *)addr;

    struct multiboot_tag* tag = (struct multiboot_tag*)(addr + 8);

    while (tag->type != MULTIBOOT_TAG_TYPE_END) {

        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                _ares_mb2_cmdline = ((struct multiboot_tag_string *) tag)->string;
                break;

            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                _ares_mb2_loader_name = ((struct multiboot_tag_string *) tag)->string;
                break;

            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                _ares_mb2_basic_meminfo = ((struct multiboot_tag_basic_meminfo *) tag);
                break;

            case MULTIBOOT_TAG_TYPE_BOOTDEV:
                _ares_mb2_bootdev = ((struct multiboot_tag_bootdev *) tag);
                break;

            case MULTIBOOT_TAG_TYPE_MMAP:
                _ares_mb2_memmap = ((struct multiboot_tag_mmap *) tag);
                break;

            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
                _ares_mb2_framebuffer = ((struct multiboot_tag_framebuffer *) tag);

                break;

            default:
                break;
        }

        // Advance to next tag (8-byte aligned)
        tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7));
    }

}


void mb2_print(uint64_t addr, uint32_t magic) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        printf("multiboot2: bad magic number %d\n", magic);
        return;
    }

    if (addr & 7) {
      printf("multiboot2: misaligned mbi 0x%08x\n", addr);
      return;
    }

    struct multiboot_tag* tag = (struct multiboot_tag*)addr;
    uint64_t size = *(uint64_t *)addr;

    printf("multiboot2: announced mbi size %d\n", size);

    for (tag = (struct multiboot_tag *) (addr + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
                                          + ((tag->size + 7) & ~7))) {

        printf ("Tag 0x%x, Size 0x%x\n", tag->type, tag->size);

        switch (tag->type) {
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                printf("Command line = %s\n", ((struct multiboot_tag_string *) tag)->string);
            break;

            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                printf("Boot loader name = %s\n", ((struct multiboot_tag_string *) tag)->string);
            break;

            case MULTIBOOT_TAG_TYPE_MODULE:
                printf("Module at 0x%x-0x%x. Command line %s\n",
                    ((struct multiboot_tag_module *) tag)->mod_start,
                    ((struct multiboot_tag_module *) tag)->mod_end,
                    ((struct multiboot_tag_module *) tag)->cmdline
                );
            break;

            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                printf ("mem_lower = %uKB, mem_upper = %uKB\n",
                    ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower,
                    ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper
                );
            break;

            case MULTIBOOT_TAG_TYPE_BOOTDEV:
                printf ("Boot device 0x%x,%u,%u\n",
                    ((struct multiboot_tag_bootdev *) tag)->biosdev,
                    ((struct multiboot_tag_bootdev *) tag)->slice,
                    ((struct multiboot_tag_bootdev *) tag)->part
                );
            break;

            case MULTIBOOT_TAG_TYPE_MMAP: {
                multiboot_memory_map_t *mmap;

                printf ("mmap\n");

                for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
                     (multiboot_uint8_t *) mmap < (multiboot_uint8_t *) tag + tag->size;
                     mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + ((struct multiboot_tag_mmap *) tag)->entry_size)) {
                    printf(" base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
                        (unsigned) (mmap->addr >> 32),
                        (unsigned) (mmap->addr & 0xffffffff),
                        (unsigned) (mmap->len >> 32),
                        (unsigned) (mmap->len & 0xffffffff),
                        (unsigned) mmap->type
                    );
                }
            }
            break;

            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER: {
                printf(" framebuffer\n");
                break;
            }

        }

    }

    tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
                                  + ((tag->size + 7) & ~7));

    printf ("Total mbi size 0x%x\n", (unsigned) tag - addr);
}
