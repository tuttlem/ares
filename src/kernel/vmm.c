
#include "vmm.h"

#define VMM_PML4_INDEX(x) (((x) >> 39) & 0x1FF)
#define VMM_PDP_INDEX(x)  (((x) >> 30) & 0x1FF)
#define VMM_PD_INDEX(x)   (((x) >> 21) & 0x1FF)
#define VMM_PT_INDEX(x)   (((x) >> 12) & 0x1FF)

void vmm_map(uint64_t virt_addr, uint64_t phys_addr, uint64_t flags) {
    uint64_t pml4_index = VMM_PML4_INDEX(virt_addr);
    uint64_t pdpt_index = VMM_PDP_INDEX(virt_addr);
    uint64_t pd_index   = VMM_PD_INDEX(virt_addr);
    uint64_t pt_index   = VMM_PT_INDEX(virt_addr);

    // Only PT level is used in static early mapping. These assume identity mappings
    pt[pt_index].value = 0;
    pt[pt_index].bits.present = 1;
    pt[pt_index].bits.writable = (flags & PAGE_RW) ? 1 : 0;
    pt[pt_index].bits.user = (flags & PAGE_USER) ? 1 : 0;
    pt[pt_index].bits.phys_addr = phys_addr >> 12;
    pt[pt_index].bits.nx = (flags & PAGE_NX) ? 1 : 0;
}

void vmm_map_range(uint64_t virt_addr, uint64_t phys_addr, uint64_t size, uint64_t flags) {
    uint64_t end = phys_addr + size;

    while (phys_addr < end) {
        vmm_map(virt_addr, phys_addr, flags);
        virt_addr += 0x1000;
        phys_addr += 0x1000;
    }
}


void vmm_unmap(uint64_t virt_addr) {
    uint64_t pt_index = (virt_addr >> 12) & 0x1FF;
    pt[pt_index].value = 0;
}

void vmm_unmap_zero_page() {
    pd[0].value = 0;
}