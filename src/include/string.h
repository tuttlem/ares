
/*
 * Ares 64-bit operating system
 *
 * Basic string operations
 */

#ifndef __ares_string_h_

#define __ares_string_h_

#include <types.h>

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
size_t strnlen(const char *s, size_t n);
size_t strlen(const char *s);
char* strstr(const char *s1, const char *s2);
char* strcpy(char *dest, const char *src);
char* strncpy(char *dest, const char *src, size_t n);

void* memset(void *s, u8 c, size_t n);
void* memcpy(void *d, const void *s, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif /* __ares_string_h_ */
