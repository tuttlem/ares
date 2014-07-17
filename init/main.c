
#include <kernel.h>
#include <idt.h>
#include <cpuid.h>

void main() {
   idt_init();
   // pit_init(50);

   u32 w[4];
   cpuid_get(CPUID_GETVENDORSTRING, w);
   int i = 0;
   char *s = (char *)w;
   
   printf("%c%c%c%c", s[4], s[5], s[6], s[7]); 			/* ebx */
   printf("%c%c%c%c", s[0], s[1], s[2], s[3]);			/* eax */
   printf("%c%c%c%c", s[12], s[13], s[14], s[15]);		/* edx */
   printf("%c%c%c%c", s[8], s[9], s[10], s[11]);		/* ecx */
   

   while (1);
}

