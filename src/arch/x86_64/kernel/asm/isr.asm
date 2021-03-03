; ----------------------------------------------------
; Ares 64-bit operating system
;
; Interrupt service routine module
; ----------------------------------------------------
;[BITS 64]

[GLOBAL idt_write]

[EXTERN isr_handler]
[EXTERN irq_handler]

%macro push_all 0
   push  rax
   push  rcx
   push  rdx
   push  rbx
   push  rsp
   push  rbp
   push  rsi
   push  rdi
%endmacro

%macro pop_all 0
   pop  rdi
   pop  rsi
   pop  rbp
   pop  rsp
   pop  rbx
   pop  rdx
   pop  rcx
   pop  rax
%endmacro

%macro isr_noerr 1
   global isr_%1

   isr_%1:
      cli
      push  0
      push  %1
      jmp   isr_common
%endmacro

%macro isr_err 1
   global isr_%1

   isr_%1:
      cli
      push  %1
      jmp   isr_common
%endmacro

%macro irq 2
   global irq_%1

   irq_%1:
      cli
      push  0
      push  %2
      jmp   irq_common
%endmacro

[SECTION .text]

isr_noerr 0
isr_noerr 1
isr_noerr 2
isr_noerr 3
isr_noerr 4
isr_noerr 5
isr_noerr 6
isr_noerr 7
isr_err   8
isr_noerr 9
isr_err   10
isr_err   11
isr_err   12
isr_err   13
isr_err   14
isr_noerr 15
isr_noerr 16
isr_noerr 17
isr_noerr 18
isr_noerr 19
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_noerr 30
isr_noerr 31

irq       0,  32
irq       1,  33
irq       2,  34
irq       3,  35
irq       4,  36
irq       5,  37
irq       6,  38
irq       7,  39
irq       8,  40
irq       9,  41
irq       10, 42
irq       11, 43
irq       12, 44
irq       13, 45
irq       14, 46
irq       15, 47


isr_common:

   push_all

   mov   ax, ds         ; save the data segment
   push  rax

   mov   ax, 0x10       ; set the data segment
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax

   call  isr_handler

   pop   rbx            ; restore the data segment
   mov   ds, bx
   mov   es, bx
   mov   fs, bx
   mov   gs, bx

   pop_all

   add   rsp, 16        ; adjust the stack for both the
                        ; interrupt number and error code
                        ; that was pushed prior to jmp
   
   sti

   iretq

irq_common:

   push_all

   mov   ax, ds         ; save the data segment
   push  rax

   mov   ax, 0x10       ; set the data segment
   mov   ds, ax
   mov   es, ax
   mov   fs, ax
   mov   gs, ax

   call  irq_handler
   
   pop   rbx            ; restore the data segment
   mov   ds, bx
   mov   es, bx
   mov   fs, bx
   mov   gs, bx

   pop_all

   add   rsp, 16        ; adjust the stack for both the
                        ; interrupt number and error code
                        ; that was pushed prior to jmp
   
   sti

   iretq

