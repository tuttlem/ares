
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

int memcmp(const void *s1, const void *s2, size_t n) {
  u8 *p = s1;
  u8 *q = s2;

  if (s1 == s2) {
    return 0;
  }

  while (n > 0) {
    if (*p != *q) {
      return (*p > *q) ? 1 : -1;
    }

    n --;
    p ++;
    q ++;
  }

  return 0;
}

int atoi(const char *s) {
  u32 len = strlen(s);
  u32 out = 0;
  u32 i;
  u32 pow = 1;

  for (i = len; i > 0; --i) {
    out += (s[i-1] - 48) * pow;
    pow *= 10;
  }

  return out;
}

char* strtok(char *s, const char *delim, char **saveptr) {
  char *token;

  if (s == NULL) {
    s = *saveptr;
  }

  s += strspn(s, delim);
  if (*s == '\0') {
    *saveptr = s;
    return NULL;
  }

  token = s;
  s = strpbrk(token, delim);
  if (s == NULL) {
    *saveptr = (char*)lfind(token, '\0');
  } else {
    *s = '\0';
    *saveptr = s + 1;
  }

  return token;
}

size_t lfind(const char *s, const char accept) {
  size_t i = 0;
  while (s[i] != accept) {
    i ++;
  }

  return (size_t)(s) + i;
}

size_t rfind(const char *s, const char accept) {
  size_t i = strlen(s) - 1;
  while (s[i] != accept) {
    if (i == 0) {
      return U32_MAX;
    }

    i ++;
  }

  return (size_t)(s) + i;
}

size_t strspn(const char *str, const char *accept) {
  const char *ptr = str;
  const char *acc;

  while (*str) {
    for (acc = accept; *acc; ++acc) {
      if (*str == *acc) {
        break;
      }
    }

    if (*acc == '\0') {
      break;
    }

    str ++;
  }

  return str - ptr;
}

char* strpbrk(const char *str, const char *accept) {
  const char *acc = accept;

  if (!*str) {
    return NULL;
  }

  while (*str) {
    for (acc = accept; *acc; ++acc) {
      if (*str == *acc) {
        break;
      }
    }

    if (*acc) {
      break;
    }

    ++str;
  }

  if (*acc == '\0') {
    return NULL;
  }

  return (char *)str;
}
