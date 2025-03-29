#include <stdint.h>
#include <ares/types.h>
#include <ares/vmm.h>
#include <ares/log.h>
#include <string.h>



extern page_entry_t* pml4;  // comes from linker/boot.asm
extern void* alloc_page(); // (we'll define a simple one shortly)

static inline page_entry_t* get_table_entry(page_entry_t* table, size_t index, uint8_t create) {
    if (!(table[index] & PAGE_PRESENT)) {
        if (!create) return NULL;

        page_entry_t* new_table = alloc_page();
        memset(new_table, 0, PAGE_SIZE);

        table[index] = ((uint64_t)new_table & ~0xFFFULL) | PAGE_PRESENT | PAGE_RW;
    }

    return (page_entry_t*)(table[index] & ~0xFFFULL);
}

void vmm_map(uint64_t virt_addr, uint64_t phys_addr, uint64_t flags) {
    size_t pml4_i = (virt_addr >> 39) & 0x1FF;
    size_t pdpt_i = (virt_addr >> 30) & 0x1FF;
    size_t pd_i   = (virt_addr >> 21) & 0x1FF;
    size_t pt_i   = (virt_addr >> 12) & 0x1FF;

    page_entry_t* pdpt = get_table_entry(pml4, pml4_i, TRUE);
    page_entry_t* pd   = get_table_entry(pdpt, pdpt_i, TRUE);
    page_entry_t* pt   = get_table_entry(pd, pd_i, TRUE);

    pt[pt_i] = (phys_addr & ~0xFFFULL) | (flags & 0xFFF) | PAGE_PRESENT;
}

void vmm_unmap(uint64_t virt_addr) {
    size_t pml4_i = (virt_addr >> 39) & 0x1FF;
    size_t pdpt_i = (virt_addr >> 30) & 0x1FF;
    size_t pd_i   = (virt_addr >> 21) & 0x1FF;
    size_t pt_i   = (virt_addr >> 12) & 0x1FF;

    page_entry_t* pdpt = get_table_entry(pml4, pml4_i, FALSE);
    if (!pdpt) return;

    page_entry_t* pd = get_table_entry(pdpt, pdpt_i, FALSE);
    if (!pd) return;

    page_entry_t* pt = get_table_entry(pd, pd_i, FALSE);
    if (!pt) return;

    pt[pt_i] = 0;

    // 🚨 CRITICAL: Flush the TLB entry
    asm volatile("invlpg (%0)" :: "r"(virt_addr) : "memory");
}


#define MAX_PAGES 256
static uint8_t page_pool[MAX_PAGES][PAGE_SIZE];
static size_t page_index = 0;

void* alloc_page() {
    if (page_index >= MAX_PAGES) {
        log_error("Out of bootstrap pages");
        return NULL;
    }
    return page_pool[page_index++];
}