
/**
 * Ares 64-bit operating system
 *
 * Interrupt service routine module
 */

#ifndef __ares_isr_h_

#define __ares_isr_h_

#include <types.h>

#define PIC1 			0x20		/* IO base address for master PIC */
#define PIC2			0xA0		/* IO base address for slave PIC */
#define PIC1_CMD		PIC1
#define PIC1_DATA		(PIC1 + 1)
#define PIC2_CMD		PIC2
#define PIC2_DATA		(PIC2 + 1)

#define PIC_EOI			0x20		/* End of interrupt signal */

#define ICW1_ICW4		0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE		0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL		0x08		/* Level triggered (edge) mode */
#define ICW1_INIT		0x10		/* Initialization - required! */
 
#define ICW4_8086		0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO		0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM		0x10		/* Special fully nested (not) */

#define ISR0 		0  /* Divide error (#DE) */
#define ISR1 		1  /* Debug (#DB) */
#define ISR2 		2  /* NMI Interrupt */
#define ISR3 		3  /* Breakpoint (#BP) */
#define ISR4 		4  /* Overflow (#OF) */
#define ISR5 		5  /* Bound range exceeded (#BR) */
#define ISR6 		6  /* Invalid opcode (#UD) */
#define ISR7 		7  /* Device not available (no math co-pro) (#NM) */
#define ISR8 		8  /* Double fault (#DF) */
#define ISR9 		9  /* Coprocessor segment overrun (#MF) */
#define ISR10 	   10  /* Invalid TSS (#TS) */
#define ISR11 	   11  /* Segment not present (#NP) */
#define ISR12 	   12  /* Stack segment fault (#SS) */
#define ISR13 	   13  /* General protection (#GP) */
#define ISR14 	   14  /* Page fault (#PF) */
#define ISR15 	   15  /* Reserved */
#define ISR16 	   16  /* Floating-point error (#MF) */
#define ISR17 	   17  /* Alignment check (#AC) */
#define ISR18 	   18  /* Machine check (#MC) */
#define ISR19 	   19  /* SIMD floating point exception (#XM) */ 

/**** Reserved ISRs ****/
#define ISR20 	   20
#define ISR21 	   21
#define ISR22 	   22
#define ISR23 	   23
#define ISR24 	   24
#define ISR25 	   25
#define ISR26 	   26
#define ISR27 	   27
#define ISR28 	   28
#define ISR29 	   29
#define ISR30 	   30
#define ISR31 	   31

#define IRQ0       32 	/* Timer */
#define IRQ1       33	/* Keyboard */
#define IRQ2       34	/* Unused */
#define IRQ3       35	/* COM 2 */
#define IRQ4       36 	/* COM 1 */
#define IRQ5       37 	/* LPT 2 */
#define IRQ6       38 	/* FDD */
#define IRQ7       39 	/* LPT 1 */
#define IRQ8       40 	/* CMOS realtime clock */
#define IRQ9       41 	/* Unused */
#define IRQ10      42	/* Unused */
#define IRQ11      43	/* Unused */
#define IRQ12      44	/* PS/2 mouse */
#define IRQ13      45	/* Unused */
#define IRQ14      46	/* Unused */
#define IRQ15      47	/* Unused */

struct _registers {
	u64 ds;                                         /* once off push */
	u64 rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;     /* provided by push_all */
	u64 int_no, err_code;                           /* provided by the macro */
    u64 rip, cs, rflags, user_rsp, user_ss;         /* provided by the processor */
};

/* Format of an interrupt handler */
typedef void (*_isr)(struct _registers);

/* Initializes the interrupt handler system */
void interrupt_init(void);

/* Provides access to handle an interrupt */
void interrupt_register_handler(u8 n, _isr handler);

/* external isr and irq defs */
extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

extern void irq_0();
extern void irq_1();
extern void irq_2();
extern void irq_3();
extern void irq_4();
extern void irq_5();
extern void irq_6();
extern void irq_7();
extern void irq_8();
extern void irq_9();
extern void irq_10();
extern void irq_11();
extern void irq_12();
extern void irq_13();
extern void irq_14();
extern void irq_15();

#endif
