
#include <idt.h>

/* Each entry in the table */
struct _idt_entry idt[256] __attribute__((aligned(0x1000)));

/* Sets up a single gate in the IDT */
void idt_set(uint8_t gate, uint64_t off, uint16_t sel, uint8_t flags) {
   idt[gate].low_off = off & 0xffff;
   idt[gate].mid_off = (off >> 16) & 0xffff;
   idt[gate].hi_off  = (off >> 32) & 0xffffffff;

   idt[gate].sel = sel;
   idt[gate].flags = flags;

   idt[gate].zero0 = 0;
   idt[gate].zero1 = 0;
}

/* Writes a new value for the idt */
static inline void lidt(void *base, uint16_t size) {
  struct {
    uint16_t length;
    uint64_t base;
  } __attribute__((packed)) IDTR;

  IDTR.length = size;
  IDTR.base = (uint64_t)base;

  asm volatile ("lidt (%0)" : : "p"(&IDTR));
}

/* Initializes the idt */
void idt_init() {
   /* initialize the interrupt handler system */
   interrupt_init();   
   
   /* start with a blank table */
   memset(&idt, 0, sizeof(struct _idt_entry) * 256);

   /* setup ISR entries in the idt */
   idt_set(ISR0,  (uint64_t)isr_0,  0x08, 0x8e);
   idt_set(ISR1,  (uint64_t)isr_1,  0x08, 0x8e);
   idt_set(ISR2,  (uint64_t)isr_2,  0x08, 0x8e);
   idt_set(ISR3,  (uint64_t)isr_3,  0x08, 0x8e);
   idt_set(ISR4,  (uint64_t)isr_4,  0x08, 0x8e);
   idt_set(ISR5,  (uint64_t)isr_5,  0x08, 0x8e);
   idt_set(ISR6,  (uint64_t)isr_6,  0x08, 0x8e);
   idt_set(ISR7,  (uint64_t)isr_7,  0x08, 0x8e);
   idt_set(ISR8,  (uint64_t)isr_8,  0x08, 0x8e);
   idt_set(ISR9,  (uint64_t)isr_9,  0x08, 0x8e);
   idt_set(ISR10, (uint64_t)isr_10, 0x08, 0x8e);
   idt_set(ISR11, (uint64_t)isr_11, 0x08, 0x8e);
   idt_set(ISR12, (uint64_t)isr_12, 0x08, 0x8e);
   idt_set(ISR13, (uint64_t)isr_13, 0x08, 0x8e);
   idt_set(ISR14, (uint64_t)isr_14, 0x08, 0x8e);
   idt_set(ISR15, (uint64_t)isr_15, 0x08, 0x8e);
   idt_set(ISR16, (uint64_t)isr_16, 0x08, 0x8e);
   idt_set(ISR17, (uint64_t)isr_17, 0x08, 0x8e);
   idt_set(ISR18, (uint64_t)isr_18, 0x08, 0x8e);
   idt_set(ISR19, (uint64_t)isr_19, 0x08, 0x8e);
   idt_set(ISR20, (uint64_t)isr_20, 0x08, 0x8e);
   idt_set(ISR21, (uint64_t)isr_21, 0x08, 0x8e);
   idt_set(ISR22, (uint64_t)isr_22, 0x08, 0x8e);
   idt_set(ISR23, (uint64_t)isr_23, 0x08, 0x8e);
   idt_set(ISR24, (uint64_t)isr_24, 0x08, 0x8e);
   idt_set(ISR25, (uint64_t)isr_25, 0x08, 0x8e);
   idt_set(ISR26, (uint64_t)isr_26, 0x08, 0x8e);
   idt_set(ISR27, (uint64_t)isr_27, 0x08, 0x8e);
   idt_set(ISR28, (uint64_t)isr_28, 0x08, 0x8e);
   idt_set(ISR29, (uint64_t)isr_29, 0x08, 0x8e);
   idt_set(ISR30, (uint64_t)isr_30, 0x08, 0x8e);
   idt_set(ISR31, (uint64_t)isr_31, 0x08, 0x8e);

   /* setup the IRQ entries in the idt */
   idt_set(IRQ0,  (uint64_t)irq_0,  0x08, 0x8e);
   idt_set(IRQ1,  (uint64_t)irq_1,  0x08, 0x8e);
   idt_set(IRQ2,  (uint64_t)irq_2,  0x08, 0x8e);
   idt_set(IRQ3,  (uint64_t)irq_3,  0x08, 0x8e);
   idt_set(IRQ4,  (uint64_t)irq_4,  0x08, 0x8e);
   idt_set(IRQ5,  (uint64_t)irq_5,  0x08, 0x8e);
   idt_set(IRQ6,  (uint64_t)irq_6,  0x08, 0x8e);
   idt_set(IRQ7,  (uint64_t)irq_7,  0x08, 0x8e);
   idt_set(IRQ8,  (uint64_t)irq_8,  0x08, 0x8e);
   idt_set(IRQ9,  (uint64_t)irq_9,  0x08, 0x8e);
   idt_set(IRQ10, (uint64_t)irq_10, 0x08, 0x8e);
   idt_set(IRQ11, (uint64_t)irq_11, 0x08, 0x8e);
   idt_set(IRQ12, (uint64_t)irq_12, 0x08, 0x8e);
   idt_set(IRQ13, (uint64_t)irq_13, 0x08, 0x8e);
   idt_set(IRQ14, (uint64_t)irq_14, 0x08, 0x8e);
   idt_set(IRQ15, (uint64_t)irq_15, 0x08, 0x8e);

   /* load the idt */
   lidt(&idt, (sizeof(struct _idt_entry) * 256) - 1);

   /* enable interrupts */
   asm volatile ("sti");
}
