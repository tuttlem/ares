#include "pmm.h"

#include <ares/multiboot2.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 4096

static uint8_t* pmm_bitmap     = NULL;
static size_t total_pages      = 0;
static size_t used_pages       = 0;
static uintptr_t pmm_base_addr = 0;

extern struct multiboot_tag_mmap* _ares_mb2_memmap;

void pmm_init(uint32_t memory_base, uint32_t memory_size) {
    pmm_base_addr = memory_base;
    total_pages = memory_size / PAGE_SIZE;

    size_t bitmap_size_bytes = total_pages / 8;

    // We'll place the bitmap just above the usable memory base
    pmm_bitmap = (uint8_t*)memory_base;

    // Mark all pages as used initially
    memset(pmm_bitmap, 0xFF, bitmap_size_bytes);
    used_pages = total_pages;

    // Free all pages except the ones the bitmap uses
    size_t bitmap_pages = (bitmap_size_bytes + PAGE_SIZE - 1) / PAGE_SIZE;

    for (size_t i = bitmap_pages; i < total_pages; i++) {
        uintptr_t addr = memory_base + (i * PAGE_SIZE);
        pmm_free((void*)addr);
    }
}

void pmm_init_from_mb2() {
    multiboot_memory_map_t *mmap;
    struct multiboot_tag* tag = (struct multiboot_tag*)_ares_mb2_memmap;

    for (mmap = _ares_mb2_memmap->entries;
         (multiboot_uint8_t *) mmap < (multiboot_uint8_t *) tag + tag->size;
         mmap = (multiboot_memory_map_t *) ((unsigned long) mmap + (_ares_mb2_memmap->entry_size))) {

      printf("memmap -> base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x\n",
                        (unsigned) (mmap->addr >> 32),
                        (unsigned) (mmap->addr & 0xffffffff),
                        (unsigned) (mmap->len >> 32),
                        (unsigned) (mmap->len & 0xffffffff),
                        (unsigned) mmap->type
                    );

      if (mmap->type == 1) {
        pmm_init(mmap->addr, mmap->len);
        break;
      }
    }
}

void* pmm_alloc() {
    for (size_t i = 0; i < total_pages; i++) {
        size_t byte = i / 8;
        size_t bit = i % 8;

        if (!(pmm_bitmap[byte] & (1 << bit))) {
            // Found a free page
            pmm_bitmap[byte] |= (1 << bit);
            used_pages++;
            return (void*)(pmm_base_addr + i * PAGE_SIZE);
        }
    }

    return NULL;
}

void pmm_free(void* addr) {
    uintptr_t paddr = (uintptr_t)addr;
    if (paddr < pmm_base_addr) return;  // Invalid free

    size_t index = (paddr - pmm_base_addr) / PAGE_SIZE;
    size_t byte = index / 8;
    size_t bit = index % 8;

    if (pmm_bitmap[byte] & (1 << bit)) {
        pmm_bitmap[byte] &= ~(1 << bit);
        used_pages--;
    }
}

size_t pmm_get_used() {
    return used_pages;
}

size_t pmm_get_total() {
    return total_pages;
}
