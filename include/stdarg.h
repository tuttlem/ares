
/*
 * phoenix/include/stdarg.h
 *
 * Variable argument definitions
 */

#ifndef __phoenix_stdarg_h_

#define __phoenix_stdarg_h_

typedef char *va_list;

#define __va_rounded_size(TYPE)                                         \
   (((sizeof(TYPE) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))

#define va_start(AP, LASTARG)                                           \
    AP = ((char *) &(LASTARG) + __va_rounded_size(LASTARG))

void va_end(va_list);

#define va_end(AP)

#define va_arg(AP, TYPE)                                                \
   (AP += __va_rounded_size(TYPE),                                      \
    *((TYPE *) (AP - __va_rounded_size(TYPE))))

#endif /* __phoenix_stdarg_h_ */
