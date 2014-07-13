OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_entry)

VIRT_BASE = 0xFFFFFFFF80000000;

SECTIONS
{
   . = 0x100000;

   .boot :
   {
      *(.mbheader)
      _loadStart = .;
      *(.boot)
      . = ALIGN(4096);

      /* Pml4 -> Page map level 4 (after boot) */
      pml4 = .;
      . += 0x1000;

      /* Pdpt -> Page directory pointer table (4096 bytes after Pml4) */
      pdpt = .;
      . += 0x1000;

      /* Pd -> Page directory (4096 bytes after Pdpt) */
      pd = .;
      . += 0x1000;
      . += 0x8000;
      _stack = .;
   }

   . += VIRT_BASE;

   .text ALIGN(0x1000) : AT(ADDR(.text) - VIRT_BASE)
   {
      *(.text)
      *(.gnu.linkonce.t*)
   }

   .data ALIGN(0x1000) : AT(ADDR(.data) - VIRT_BASE)
   {
      *(.data)
      *(.gnu.linkonce.d*)
   }

   .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - VIRT_BASE)
   {
      *(.rodata*)
      *(.gnu.linkonce.r*)
   }

   _loadEnd = . - VIRT_BASE;

   .bss ALIGN(0x1000) : AT(ADDR(.bss) - VIRT_BASE)
   {
      *(COMMON)
      *(.bss)
      *(.gnu.linkonce.b*)
   }

   _bssEnd = . - VIRT_BASE;

   /DISCARD/ :
   {
      *(.comment)
      *(.eh_frame)
   }
}

