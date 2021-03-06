; ----------------------------------------------------
; Ares 64-bit operating system
;
; Spinlock implementation
; ----------------------------------------------------
;[BITS 64]

[SECTION .data]
locked:
  dd      0

[SECTION .text]
global spin_lock
global spin_unlock

spin_lock:
   mov    eax, 1
trylock:
   xchg   eax, [rdi]

   test   eax, eax
   jnz    trylock
   
   ret

spin_unlock:

   xor    eax, eax
   xchg   eax, [rdi]

   ret

