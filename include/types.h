
/**
 * Ares 64-bit operating system
 *
 * Common type definitions
 */

#ifndef __ares_types_h_

#define __ares_types_h_

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
typedef          long ssize_t;
#endif

/* Standard integer types */
typedef unsigned char  		u8;
typedef          char  		s8;
typedef unsigned short 		u16;
typedef          short 		s16;
typedef unsigned int   		u32;
typedef          int   		s32;
typedef unsigned long long 	u64;
typedef          long long 	s64;

#ifdef __64BIT__
typedef unsigned long long uintmax_t;
typedef long long           intmax_t;
#else
typedef unsigned int       uintmax_t;
typedef int                 intmax_t;
#endif

/* abstract pointer type */
typedef void*          type_t;

#endif /* __ares_types_h_ */
