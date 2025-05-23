
/**
 * Ares 64-bit operating system
 *
 * cpuid module
 */

#ifndef __ares_cpuid_h_

#define __ares_cpuid_h_

#include <types.h>
#include <io.h>

#include <kernel.h>

#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" 
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA          "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"

#define CPUID_FEAT_ECX_SSE3       (1 << 0 )
#define CPUID_FEAT_ECX_PCLMUL     (1 << 1 )
#define CPUID_FEAT_ECX_DTES64     (1 << 2 )
#define CPUID_FEAT_ECX_MONITOR    (1 << 3 ) 
#define CPUID_FEAT_ECX_DS_CPL     (1 << 4 ) 
#define CPUID_FEAT_ECX_VMX        (1 << 5 ) 
#define CPUID_FEAT_ECX_SMX        (1 << 6 ) 
#define CPUID_FEAT_ECX_EST        (1 << 7 ) 
#define CPUID_FEAT_ECX_TM2        (1 << 8 ) 
#define CPUID_FEAT_ECX_SSSE3      (1 << 9 ) 
#define CPUID_FEAT_ECX_CID        (1 << 10)
#define CPUID_FEAT_ECX_FMA        (1 << 12)
#define CPUID_FEAT_ECX_CX16       (1 << 13) 
#define CPUID_FEAT_ECX_ETPRD      (1 << 14) 
#define CPUID_FEAT_ECX_PDCM       (1 << 15) 
#define CPUID_FEAT_ECX_DCA        (1 << 18) 
#define CPUID_FEAT_ECX_SSE4_1     (1 << 19) 
#define CPUID_FEAT_ECX_SSE4_2     (1 << 20) 
#define CPUID_FEAT_ECX_x2APIC     (1 << 21) 
#define CPUID_FEAT_ECX_MOVBE      (1 << 22) 
#define CPUID_FEAT_ECX_POPCNT     (1 << 23) 
#define CPUID_FEAT_ECX_AES        (1 << 25) 
#define CPUID_FEAT_ECX_XSAVE      (1 << 26) 
#define CPUID_FEAT_ECX_OSXSAVE    (1 << 27) 
#define CPUID_FEAT_ECX_AVX        (1 << 28)

#define CPUID_FEAT_EDX_FPU        (1 << 0 ) 
#define CPUID_FEAT_EDX_VME        (1 << 1 ) 
#define CPUID_FEAT_EDX_DE         (1 << 2 ) 
#define CPUID_FEAT_EDX_PSE        (1 << 3 ) 
#define CPUID_FEAT_EDX_TSC        (1 << 4 ) 
#define CPUID_FEAT_EDX_MSR        (1 << 5 ) 
#define CPUID_FEAT_EDX_PAE        (1 << 6 ) 
#define CPUID_FEAT_EDX_MCE        (1 << 7 ) 
#define CPUID_FEAT_EDX_CX8        (1 << 8 ) 
#define CPUID_FEAT_EDX_APIC       (1 << 9 ) 
#define CPUID_FEAT_EDX_SEP        (1 << 11) 
#define CPUID_FEAT_EDX_MTRR       (1 << 12) 
#define CPUID_FEAT_EDX_PGE        (1 << 13) 
#define CPUID_FEAT_EDX_MCA        (1 << 14) 
#define CPUID_FEAT_EDX_CMOV       (1 << 15) 
#define CPUID_FEAT_EDX_PAT        (1 << 16) 
#define CPUID_FEAT_EDX_PSE36      (1 << 17) 
#define CPUID_FEAT_EDX_PSN        (1 << 18) 
#define CPUID_FEAT_EDX_CLF        (1 << 19) 
#define CPUID_FEAT_EDX_DTES       (1 << 21) 
#define CPUID_FEAT_EDX_ACPI       (1 << 22) 
#define CPUID_FEAT_EDX_MMX        (1 << 23) 
#define CPUID_FEAT_EDX_FXSR       (1 << 24) 
#define CPUID_FEAT_EDX_SSE        (1 << 25) 
#define CPUID_FEAT_EDX_SSE2       (1 << 26) 
#define CPUID_FEAT_EDX_SS         (1 << 27) 
#define CPUID_FEAT_EDX_HTT        (1 << 28) 
#define CPUID_FEAT_EDX_TM1        (1 << 29) 
#define CPUID_FEAT_EDX_IA64       (1 << 30)
#define CPUID_FEAT_EDX_PBE        (1 << 31)

#define CPUID_GETVENDORSTRING	  	0x00000000
#define CPUID_GETFEATURES		  	0x00000001
#define CPUID_GETTLB			  	0x00000002
#define CPUID_GETSERIAL			  	0x00000003

#define CPUID_INTELEXTENDED 	  	0x80000000
#define CPUID_INTELFEATURES			0x80000001
#define CPUID_INTELBRANDSTRING 		0x80000002
#define CPUID_INTELBRANDSTRINGMORE 	0x80000003
#define CPUID_INTELBRANDSTRINGEND 	0x80000004


/* Get a complete cpuid request */
static inline void cpuid_get(uint64_t code, uint32_t str[4]) {
  asm volatile( "cpuid" : "=a" (*str),
  						  "=b" (*(str+1)),
  						  "=c" (*(str+2)),
  						  "=d" (*(str+3))
  						: "a"(code));	
}

/* Diagnostic print of a cpuid result */
void cpuid_diag(uint32_t str[4]);

#endif /* __ares_cpuid_h_ */
