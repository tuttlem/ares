/**
 * Ares 64-bit operating system
 *
 * Virtual memory mapping
 */

#ifndef __ares_vmm_h_

#define __ares_vmm_h_


#include <stdint.h>

#define PAGE_PRESENT    0x001
#define PAGE_RW         0x002
#define PAGE_USER       0x004
#define PAGE_PWT        0x008
#define PAGE_PCD        0x010
#define PAGE_ACCESSED   0x020
#define PAGE_DIRTY      0x040
#define PAGE_PAT        0x080
#define PAGE_GLOBAL     0x100
#define PAGE_NX         (1ULL << 63)

#define PAGE_ENTRIES    512
#define PAGE_SIZE       0x1000

#define ALIGN_UP(x, a)   (((x) + ((a) - 1)) & ~((a) - 1))
#define ALIGN_DOWN(x, a) ((x) & ~((a) - 1))


// Bitfield structure for all four paging levels
typedef union {
    struct {
        uint64_t present         : 1;
        uint64_t writable        : 1;
        uint64_t user            : 1;
        uint64_t write_through   : 1;
        uint64_t cache_disabled  : 1;
        uint64_t accessed        : 1;
        uint64_t ignored1        : 1;
        uint64_t must_be_zero    : 1;  // or must_be_one in 2MB/1GB pages
        uint64_t ignored2        : 1;
        uint64_t available       : 3;
        uint64_t phys_addr       : 40;
        uint64_t available_high  : 11;
        uint64_t nx              : 1;
    } __attribute__((packed)) bits;
    uint64_t value;
} pml4e_t, pdpe_t, pde_t, pte_t;

extern pml4e_t pml4[];
extern pdpe_t pdpt[];
extern pde_t pd[];
extern pte_t pt[];

void vmm_map(uint64_t virt_addr, uint64_t phys_addr, uint64_t flags);
void vmm_map_range(uint64_t virt_addr, uint64_t phys_addr, uint64_t size, uint64_t flags);
void vmm_unmap(uint64_t virt_addr);
void vmm_unmap_zero_page();

#endif
