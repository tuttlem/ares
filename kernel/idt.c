
#include <idt.h>

/* Each entry in the table */
struct _idt_entry idt[256] __attribute__((aligned(0x1000)));

/* Pointer to the table */
struct _idt idt_ptr;
u64 idt_addr = (u64)&idt_ptr;

/* Writes the idt */
extern void idt_write(u64);

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


/* Sets up a single gate in the IDT */
void idt_set(u8 gate, u64 off, u16 sel, u8 flags) {
   idt[gate].low_off = off & 0xffff;
   idt[gate].mid_off = (off >> 16) & 0xffff;
   idt[gate].hi_off  = (off >> 32) & 0xffffffff;

   idt[gate].sel = sel;
   idt[gate].flags = flags;

   idt[gate].zero0 = 0;
   idt[gate].zero1 = 0;
}

/* Initializes the idt */
void idt_init() {
   /* initialize the interrupt handler system */
   interrupt_init();   
   
   /* start with a blank table */
   memset(&idt, 0, sizeof(struct _idt_entry) * 256);

   /* setup the table pointer */
   idt_ptr.limit = (sizeof(struct _idt_entry) * 256) - 1;
   idt_ptr.base  = (u64)&idt;

   /* Re-map the irq table to use ISRs 32 -> 47 */
   irq_remap(0x20, 0x28);

   /* setup ISR entries in the idt */
   idt_set(ISR0,  (u64)isr_0,  0x08, 0x8e);
   idt_set(ISR1,  (u64)isr_1,  0x08, 0x8e);
   idt_set(ISR2,  (u64)isr_2,  0x08, 0x8e);
   idt_set(ISR3,  (u64)isr_3,  0x08, 0x8e);
   idt_set(ISR4,  (u64)isr_4,  0x08, 0x8e);
   idt_set(ISR5,  (u64)isr_5,  0x08, 0x8e);
   idt_set(ISR6,  (u64)isr_6,  0x08, 0x8e);
   idt_set(ISR7,  (u64)isr_7,  0x08, 0x8e);
   idt_set(ISR8,  (u64)isr_8,  0x08, 0x8e);
   idt_set(ISR9,  (u64)isr_9,  0x08, 0x8e);
   idt_set(ISR10, (u64)isr_10, 0x08, 0x8e);
   idt_set(ISR11, (u64)isr_11, 0x08, 0x8e);
   idt_set(ISR12, (u64)isr_12, 0x08, 0x8e);
   idt_set(ISR13, (u64)isr_13, 0x08, 0x8e);
   idt_set(ISR14, (u64)isr_14, 0x08, 0x8e);
   idt_set(ISR15, (u64)isr_15, 0x08, 0x8e);
   idt_set(ISR16, (u64)isr_16, 0x08, 0x8e);
   idt_set(ISR17, (u64)isr_17, 0x08, 0x8e);
   idt_set(ISR18, (u64)isr_18, 0x08, 0x8e);
   idt_set(ISR19, (u64)isr_19, 0x08, 0x8e);
   idt_set(ISR20, (u64)isr_20, 0x08, 0x8e);
   idt_set(ISR21, (u64)isr_21, 0x08, 0x8e);
   idt_set(ISR22, (u64)isr_22, 0x08, 0x8e);
   idt_set(ISR23, (u64)isr_23, 0x08, 0x8e);
   idt_set(ISR24, (u64)isr_24, 0x08, 0x8e);
   idt_set(ISR25, (u64)isr_25, 0x08, 0x8e);
   idt_set(ISR26, (u64)isr_26, 0x08, 0x8e);
   idt_set(ISR27, (u64)isr_27, 0x08, 0x8e);
   idt_set(ISR28, (u64)isr_28, 0x08, 0x8e);
   idt_set(ISR29, (u64)isr_29, 0x08, 0x8e);
   idt_set(ISR30, (u64)isr_30, 0x08, 0x8e);
   idt_set(ISR31, (u64)isr_31, 0x08, 0x8e);

   /* setup the IRQ entries in the idt */
   idt_set(IRQ0,  (u64)irq_0,  0x08, 0x8e);
   idt_set(IRQ1,  (u64)irq_1,  0x08, 0x8e);
   idt_set(IRQ2,  (u64)irq_2,  0x08, 0x8e);
   idt_set(IRQ3,  (u64)irq_3,  0x08, 0x8e);
   idt_set(IRQ4,  (u64)irq_4,  0x08, 0x8e);
   idt_set(IRQ5,  (u64)irq_5,  0x08, 0x8e);
   idt_set(IRQ6,  (u64)irq_6,  0x08, 0x8e);
   idt_set(IRQ7,  (u64)irq_7,  0x08, 0x8e);
   idt_set(IRQ8,  (u64)irq_8,  0x08, 0x8e);
   idt_set(IRQ9,  (u64)irq_9,  0x08, 0x8e);
   idt_set(IRQ10, (u64)irq_10, 0x08, 0x8e);
   idt_set(IRQ11, (u64)irq_11, 0x08, 0x8e);
   idt_set(IRQ12, (u64)irq_12, 0x08, 0x8e);
   idt_set(IRQ13, (u64)irq_13, 0x08, 0x8e);
   idt_set(IRQ14, (u64)irq_14, 0x08, 0x8e);
   idt_set(IRQ15, (u64)irq_15, 0x08, 0x8e);

   idt_write((u64)&idt_ptr);

   asm volatile ("sti");
}
