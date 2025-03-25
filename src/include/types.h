
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

#define FALSE   0
#define TRUE    1

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
typedef          long ssize_t;
#endif

#define uint8_t_MAX            0xFF
#define uint16_t_MAX           0xFFFF
#define uint32_t_MAX           0xFFFFFFFF
#define uint64_t_MAX           0xFFFFFFFFFFFFFFFF

/* Standard integer types */
typedef unsigned char  		uint8_t;
typedef          char  		int8_t;
typedef unsigned short 		uint16_t;
typedef          short 		int16_t;
typedef unsigned int   		uint32_t;
typedef          int   		int32_t;
typedef unsigned long long 	uint64_t;
typedef          long long 	int64_t;

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
