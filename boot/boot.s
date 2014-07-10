[BITS 32]

[SECTION .mbheader]

[EXTERN _loadStart]
[EXTERN _loadEnd]
[EXTERN _bssEnd]

ALIGN 8

;
; Multiboot2 header
;

mb_header:

   ;
   ; Multiboot header
   ;

   DD    0xE85250D6                                         ; magic
   DD    0                                                  ; architecture
   DD    mb_header_end - mb_header                          ; header_length
   DD    -(0xE85250D6 + 0 + (mb_header_end - mb_header))    ; checksum

   ;
   ; Address tag of Multiboot header
   ;

   DW    2, 0                                ; type (2), flags
   DD    24                                  ; size
   DD    mb_header                           ; header address
   DD    _loadStart                          ; text segment
   DD    _loadEnd                            ; end of text segment
   DD    _bssEnd                             ; end of the bss

   ;
   ; Entry address tag of Multiboot header
   ;

   DW    3, 0                                ; type (3), flags
   DD    12                                  ; size
   DD    _entry                              ; entry point to jump to from bootloader
   DD    0                                   ; align next tag to 8-byte boundary

   ;
   ; End of tags
   ;

   DW    0, 0                                ; type (0), flags
   DD    8                                   ; size 8
                                             ; tags terminated with type=0,size=8

mb_header_end:

;
; Boot
;

[SECTION .boot]

[GLOBAL _entry]
[EXTERN _stack]

_entry:

   mov   eax, Gdtr1                          ; load a GDT that we can trust as GRUB
   lgdt  [eax]                               ; may have left us with garbage

   push  0x08                                ; jump to segment 0x8 (our code segment)
   push  .gdt_ready                          ; 0x8 is because it's our second segment
   retf                                      ; 8 bytes after the first

.gdt_ready:

   mov   eax, 0x10                           ; load data and stack segments with 0x10
   mov   ds, ax                              ; which is our data segment (defined third)
   mov   ss, ax                              ; therefore 16 bytes after the first
   mov   esp, _stack

   call  paging_and_longmode                 ; setup paging and longmode

   mov   eax, Gdtr2                          ; re-flush the GDT
   lgdt  [Gdtr2]

   push  0x08                                ; jump into 64-bit land
   push  .gdt_ready_2
   retf

[BITS 64]

[EXTERN main]

.gdt_ready_2:

   mov   eax, 0x10                           ; re-flush all of our data segments
   mov   ds, ax
   mov   es, ax
   mov   ss, ax

   mov   rsp, _stack + 0xFFFFFFFF80000000    ; re-base the stack

   mov   rax, Gdtr3                          ; re-base the gdt
   lgdt  [rax]

   mov   rax, main                           ; jump into c-land
   call  rax

   cli
   jmp   $

[BITS 32]

[EXTERN Pml4]
[EXTERN Pdpt]
[EXTERN Pd]

;
; paging_and_longmode
;
; Sets up
paging_and_longmode:

   mov   eax, Pdpt                                       ; Pml4[0] -> Pdpt
   or    eax, 1
   mov   [Pml4], eax
   mov   [Pml4 + 0xFF8], eax

   mov   eax, Pd                                         ; Pdpt[0] -> Pd
   or    eax, 1
   mov   [Pdpt], eax
   mov   [Pdpt + 0xFF0], eax

   mov   dword [Pd]     , 0x000083
   mov   dword [Pd + 8] , 0x200083
   mov   dword [Pd + 16], 0x400083
   mov   dword [Pd + 24], 0x600083

   mov   eax, Pml4                                       ; load cr3 with Pml4
   mov   cr3, eax

   mov   eax, cr4                                        ; enable PAE
   or    eax, 1 << 5
   mov   cr4, eax

   mov   ecx, 0xC0000080                                 ; enable long mode
   rdmsr
   or    eax, 1 << 8
   wrmsr

   mov   eax, cr0                                        ; enable paging
   or    eax, 1 << 31
   mov   cr0, eax

   ret

;
; GDT definitions
;

;
; GDT takes the following structure
;
; 63 - 56: base 24:31
; 55 - 52: flags
; 51 - 48: limit 16:19
; 47 - 40: access byte
; 39 - 32: base 16:23
; 31 - 16: base 0:15
; 15 -  0: limit 0:15
;
; base (32 bits)  = linear address of where the segment begins
; limit (20 bits) = maximum addressable unit (1 byte unit or pages)
; access byte =
;     7   "Pr"   : Present bit - must be 1 for all selectors
;     6-5 "Privl": Privilege bits (ring level 0-3)
;     4          : Always 1
;     3   "Ex"   : Executable (1 for code segment, 0 for data)
;     2   "DC"   : Direction bit/Conforming bit
;        Direction for data selectors (0 segment grows up, 1 grows down)
;        Conforming for code selectors
;           1: Execution by privilege level equal or below
;           0: Execution by privilege equal ONLY
;     1   "RW"   : Readable for code selectors, Writable for data selectors
;     0   "Ac"   : CPU sets this to 1 when segment is accessed
; flags =
;     7   "Gr": Granularity - 0 for limit in bytes, 1 for limit in pages
;     6   "Sz": Size - 0 for 16 bit protected mode, 1 for 32 bit
;     5   "L" : 1 for 64 bit mode (Sz must be set to 0)
;     4   unused: set to 0
;
; LGDT expects the size and the address (offset) of the prespective GDT entries
; so first is the raw GDT values. Following the table is the definitions that
; are fed to LGDT.

TmpGdt:
; Protected mode GDT
   DQ    0x0000000000000000                              ; null descriptor
   DQ    0x00CF9A000000FFFF                              ; code segment (type 0x9A)
   DQ    0x00CF92000000FFFF                              ; data segment (type 0x92)

; Long mode GDT
; long mode doesn't support segmented memory, so there's no need
; to define a base or limit here. Its just 0000000000000000->FFFFFFFFFFFFFFFF
   DQ    0x0000000000000000                              ; null descriptor
   DQ    0x00A09A0000000000                              ; code segment (type 0x9A)
   DQ    0x00A0920000000000                              ; data segment (type 0x92)

; Protected mode GDT
Gdtr1:
   DW    23                                              ; (n-1) entries (length)
   DD    TmpGdt                                          ; first table address

; Long mode GDT
Gdtr2:
   DW    23                                              ; (n-1) entries (length)
   DD    TmpGdt + 24                                     ; second table address
   DD    0                                               ; padded end

; Long mode GDT (re-based to the kernel - see VIRT_BASE in linker script)
Gdtr3:
   DW    23                                              ; size of the table
   DQ    TmpGdt + 24 + 0xFFFFFFFF80000000                ; table start


