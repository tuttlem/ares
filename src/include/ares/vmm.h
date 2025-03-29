/**
 * Ares 64-bit operating system
 *
 * Virtual memory mapping
 */

#ifndef __ares_vmm_h_

#define __ares_vmm_h_

#define PAGE_PRESENT        0x001
#define PAGE_RW             0x002
#define PAGE_USER           0x004

#define PAGE_ENTRIES        512
#define PAGE_SIZE           0x1000

typedef uint64_t page_entry_t;

#include <stdint.h>

void vmm_map(uint64_t virt_addr, uint64_t phys_addr, uint64_t flags);
void vmm_unmap(uint64_t virt_addr);

#endif
