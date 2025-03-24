
#include "ctype.h"

int isspace(int c) {
    return c == ' '  || c == '\f' ||
           c == '\n' || c == '\r' ||
           c == '\t' || c == '\v';
}

int iscntrl(int c) {
    return (c >= 0 && c <= 31) || c == 127;
}

int isprint(int c) {
    return (c >= 32 && c <= 126);
}

int isgraph(int c) {
    return (c > 32 && c <= 126);
}

int ispunct(int c) {
    return isprint(c) && !isspace(c) && !isalnum(c);
}

int isxdigit(int c) {
    return isdigit(c) ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}