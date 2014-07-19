
#include <cpuid.h>

/* Diagnostic print of a cpuid result */
void cpuid_diag(u32 str[4]) {
	char *a = (char *)&str, 
		 *b = (char *)&str[1], 
		 *c = (char *)&str[2], 
		 *d = (char *)&str[3];

	printf("[rax] 0x%08x \"%c%c%c%c\"\n", str[0], *a, *(a+1), *(a+2), *(a+3));
	printf("[rbx] 0x%08x \"%c%c%c%c\"\n", str[2], *b, *(b+1), *(b+2), *(b+3));
	printf("[rcx] 0x%08x \"%c%c%c%c\"\n", str[3], *c, *(c+1), *(c+2), *(c+3));
	printf("[rdx] 0x%08x \"%c%c%c%c\"\n", str[3], *d, *(d+1), *(d+2), *(d+3));

}