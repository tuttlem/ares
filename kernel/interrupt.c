
#include <interrupt.h>

_isr _handlers[256];

/* Initializes the interrupt handler system */
void interrupt_init(void) {
	memset(_handlers, 0, sizeof(_isr) * 256);	
}

/* Provides access to handle an interrupt */
void interrupt_register_handler(u8 n, _isr handler) {
	_handlers[n] = handler;
}

/* Handles ISR requests */
void isr_handler(struct _registers regs) {
	
	printf("ds: %x\n", regs.ds);
	printf("rdi: %x, rsi: %x, rbp: %x, rsp: %x\n", regs.rdi, regs.rsi, regs.rbp, regs.rsp);
	printf("rbx: %x, rdx: %x, rcx: %x, rax: %x\n", regs.rbx, regs.rdx, regs.rcx, regs.rax);
	printf("int: %x, err: %x\n", regs.int_no, regs.err_code);
	printf("eip: %x, cs: %x, eflags: %x\n", regs.rip, regs.cs, regs.rflags);
	printf("user_rsp: %x, user_ss: %x\n", regs.user_rsp, regs.user_ss);
	
   
	/* on-fire the handler if we have one */
	if (_handlers[regs.int_no]) {
		_handlers[regs.int_no](regs);
	}   
}  

/* Handles IRQ requests */
void irq_handler(struct _registers regs) {

	/* send an EOI (end of interrupt) signal to the PICs
	   if this interrupt involved the slave */
	if (regs.int_no >= 40) {
		/* sends a reset signal to the slave */
		outb(PIC2_CMD, PIC_EOI);
	}

	/* sends a reset signal to the master */
	outb(PIC1_CMD, PIC_EOI);

	/* on-fire the handler if we have one */
	if (_handlers[regs.int_no]) {
		_handlers[regs.int_no](regs);
	}

}