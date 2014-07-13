
#include <string.h>

int strcmp(const char *s1, const char *s2) {
   const u8 *sp1 = (const u8 *)s1;
   const u8 *sp2 = (const u8 *)s2;
   int d = 0;

   while (*sp1 || *sp2) {
      d = *s2 - *s1;
      if (d) {
         return d;
      }
      sp1++;
      sp2++;
   }

   return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
   u8 c1, c2;

   while (n) {
      c1 = *s1++;
      c2 = *s2++;
      if (c1 != c2) return c1 < c2 ? -1 : 1;
      if (!c1) break;
      n--;
   }

   return 0;
}

size_t strnlen(const char *s, size_t n) {
   const char *sp = s;
   while (*sp && n) {
      sp++;
      n--;
   }
   return sp - s;
}

size_t strlen(const char *s) {
   const char *sp;
   for (sp = s; *sp; ++sp);
   return sp - s;
}

char* strcpy(char *dest, const char *src) {
   do {
      *dest++ = *src++;
   } while (*src != '\0');
   return dest;
}

char* strncpy(char *dest, const char *src, size_t n) {
   size_t i = n;
   do {
      *dest++ = *src++;
   } while (*src != '\0' && --i > 0);
   return dest;
}

char* strstr(const char *s1, const char *s2) {
   size_t l1, l2;

   l2 = strlen(s2);
   if (!l2) return (char *)s1;

   l1 = strlen(s1);
   while (l1 >= l2) {
      l1--;
      if (!memcmp(s1, s2, l2)) return (char *)s1;
      s1++;
   }

   return NULL;
}

void* memset(void *d, u8 c, size_t n) {
   u8 *dp = (u8 *)d;
   for (; n != 0; n --) *dp++ = c;
   return d;
}

void* memcpy(void *d, const void *s, size_t n) {
   u8 *dp = (u8 *)d;
   const u8 *sp = (const u8 *)s;
   for (; n != 0; n --) *dp++ = *sp++;
   return d;
}


