
/**
 * Ares 64-bit operating system
 *
 * Interrupt service routine module
 */

#ifndef __ares_isr_h_

#define __ares_isr_h_

#include <types.h>

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

#define IRQ0       32
#define IRQ1       33
#define IRQ2       34
#define IRQ3       35
#define IRQ4       36
#define IRQ5       37
#define IRQ6       38
#define IRQ7       39
#define IRQ8       40
#define IRQ9       41
#define IRQ10      42
#define IRQ11      43
#define IRQ12      44
#define IRQ13      45
#define IRQ14      46
#define IRQ15      47

struct _registers {
	u64 ds;                                         /* once off push */
	u64 rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax;     /* provided by push_all */
	u64 int_no, err_code;                           /* provided by the macro */
   u64 rip, cs, rflags, user_rsp, user_ss;         /* provided by the processor */
};

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
