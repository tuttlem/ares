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

   mov   eax, gdt_1                          ; load a GDT that we can trust as GRUB
   lgdt  [eax]                               ; may have left us with garbage

   push  0x08                                ; jump to segment 0x8 (our code segment)
   push  .clean_gdt                          ; 0x8 is because it's our second segment
   retf                                      ; 8 bytes after the first

.clean_gdt:

   mov   eax, 0x10                           ; load data and stack segments with 0x10
   mov   ds, ax                              ; which is our data segment (defined third)
   mov   ss, ax                              ; therefore 16 bytes after the first
   mov   esp, _stack

   mov   eax, pdpt
   or    eax, 1                                          ; mark as "present"
   mov   [pml4], eax                                     ; Pml4[0] -> Pdpt
   mov   [pml4 + 0xFF8], eax                             ; make the last entry of the pml4
                                                         ; point to the beginning of the
                                                         ; table

   mov   eax, pd
   or    eax, 1                                          ; mark as "present"
   mov   [pdpt], eax                                     ; Pdpt[0] -> Pd
   mov   [pdpt + 0xFF0], eax                             ; make the last entry of the pdpt
                                                         ; point to the beginning of the
                                                         ; table

   mov   dword [pd]     , 0x000083
   mov   dword [pd + 8] , 0x200083
   mov   dword [pd + 16], 0x400083
   mov   dword [pd + 24], 0x600083

   mov   eax, pml4                                       ; load cr3 with Pml4
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

   mov   eax, gdt_2                          ; re-flush the GDT
   lgdt  [eax]

   push  0x08                                ; jump into 64-bit land
   push  .enter_long
   retf

[BITS 64]

[EXTERN main]

.enter_long:

   mov   eax, 0x10                           ; re-flush all of our data segments
   mov   ds, ax
   mov   es, ax
   mov   ss, ax

   mov   rsp, _stack + 0xFFFFFFFF80000000    ; re-base the stack

   mov   rax, gdt_3                          ; re-base the gdt
   lgdt  [rax]

   mov   rax, main                           ; jump into c-land
   call  rax

   cli
   jmp   $

[BITS 32]

[EXTERN pml4]
[EXTERN pdpt]
[EXTERN pd]

gdt_tab:
   DQ    0x0000000000000000
   DQ    0x00CF9A000000FFFF
   DQ    0x00CF92000000FFFF
   DQ    0x0000000000000000
   DQ    0x00A09A0000000000
   DQ    0x00A0920000000000

gdt_1:
   DW    23
   DD    gdt_tab

gdt_2:
   DW    23
   DD    gdt_tab + 24
   DD    0

gdt_3:
   DW    23
   DQ    gdt_tab + 24 + 0xFFFFFFFF80000000

