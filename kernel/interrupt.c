
#include <interrupt.h>

_isr _handlers[256];

/* Remaps the slave and master PIC to re-base from a new offset */
void irq_remap(u32 offset1, u32 offset2) {

   u8 a1, a2;

   /* save current masks */
   a1 = inb(PIC1_DATA);
   a2 = inb(PIC2_DATA);

   /* start init sequence */
   outb(PIC1_CMD, ICW1_INIT + ICW1_ICW4);
   outb(PIC2_CMD, ICW1_INIT + ICW1_ICW4);

   /* write the offsets */
   outb(PIC1_DATA, offset1);
   outb(PIC2_DATA, offset2);

   /* Notify master that there is a slave at irq 2 (0000 0100) */
   outb(PIC1_DATA, 4);
   /* Notify slace of its identity (0000 0010) */
   outb(PIC2_DATA, 2);

   outb(PIC1_DATA, ICW4_8086);
   outb(PIC2_DATA, ICW4_8086);

   /* restore the saved masks */
   outb(PIC1_DATA, a1);
   outb(PIC2_DATA, a2);
}

/* Sets a bit on in the irq mask (PIC will ignore set bits) */
void irq_set_mask(u8 line) {
   u16 port;
   u8 value;

   if (line < 8) {
      port = PIC1_DATA;
   } else {
      port = PIC2_DATA;
      line -= 8;
   }

   value = inb(port) | (1 << line);
   outb(port, value);
}

/* Clears a bit on in the irq mask (PIC will respond to clear bits) */
void irq_clear_mask(u8 line) {
   u16 port;
   u8 value;

   if (line < 8) {
      port = PIC1_DATA;
   } else {
      port = PIC2_DATA;
      line -= 8;
   }

   value = inb(port) & ~(1 << line);
   outb(port, value);
}


/* Initializes the interrupt handler system */
void interrupt_init(void) {
	memset(_handlers, 0, sizeof(_isr) * 256);	

   /* Re-map the irq table to use ISRs 32 -> 47 */
   irq_remap(0x20, 0x28);	
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