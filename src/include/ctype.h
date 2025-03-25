
/**
 * Ares 64-bit operating system
 *
 * Character testing and mapping routines
 */

#ifndef __ares_ctype_h_

#define __ares_ctype_h_

static inline int isdigit(int c)   { return c >= '0' && c <= '9'; }
static inline int isalpha(int c)   { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
static inline int isalnum(int c)   { return isalpha(c) || isdigit(c); }
static inline int islower(int c)   { return c >= 'a' && c <= 'z'; }
static inline int isupper(int c)   { return c >= 'A' && c <= 'Z'; }
static inline int tolower(int c)   { return isupper(c) ? c + 32 : c; }
static inline int toupper(int c)   { return islower(c) ? c - 32 : c; }

int isspace(int c);
int isprint(int c);
int isgraph(int c);
int iscntrl(int c);
int ispunct(int c);
int isxdigit(int c);

#endif