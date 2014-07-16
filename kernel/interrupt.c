
#include <interrupt.h>

void isr_handler(struct _registers regs) {
   printf("ds: %x\n", regs.ds);
   printf("rdi: %x, rsi: %x, rbp: %x, rsp: %x\n", regs.rdi, regs.rsi, regs.rbp, regs.rsp);
   printf("rbx: %x, rdx: %x, rcx: %x, rax: %x\n", regs.rbx, regs.rdx, regs.rcx, regs.rax);
   printf("int: %x, err: %x\n", regs.int_no, regs.err_code);
   printf("eip: %x, cs: %x, eflags: %x\n", regs.rip, regs.cs, regs.rflags);
   printf("user_rsp: %x, user_ss: %x\n", regs.user_rsp, regs.user_ss);
}  