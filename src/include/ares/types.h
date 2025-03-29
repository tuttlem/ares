#ifndef ARES_TYPES_H
#define ARES_TYPES_H

#include <stdint.h>
#include <stddef.h> // for size_t and NULL

#define FALSE 0
#define TRUE  1

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef long ssize_t;

#define uint8_t_MAX   0xFF
#define uint16_t_MAX  0xFFFF
#define uint32_t_MAX  0xFFFFFFFF
#define uint64_t_MAX  0xFFFFFFFFFFFFFFFF

typedef void* type_t;

#endif /* ARES_TYPES_H */
