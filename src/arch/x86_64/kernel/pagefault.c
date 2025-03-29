
#include <types.h>
#include <interrupt.h>
#include <panic.h>
#include <stdio.h>

void _ares_page_fault_handler(struct _registers regs) {
    uint64_t cr2;
    asm volatile("mov   %%cr2, %0" : "=r"(cr2));

    printf("------------------ PAGE FAULT REPORT ------------------ \n");
    printf("CR2 = %x\n", cr2);
    printf("Error code = %c\n", regs.err_code);

    if (regs.err_code & 0x1) {
        printf("  -> Page protection violation\n");
    } else {
        printf("  -> Page not present\n");
    }

    if (regs.err_code & 0x2) {
        printf("  -> Write access\n");
    } else {
        printf("  -> Read access\n");
    }

    if (regs.err_code & 0x4) {
        printf("  -> From user mode\n");
    } else {
        printf("  -> From supervisor mode\n");
    }

    printf("------------------------------------------------------- \n");

    PANIC("Unhandled page fault");
}