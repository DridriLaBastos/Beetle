#ifndef __BEETLE_LIBC_STRING_H__
#define __BEETLE_LIBC_STRING_H__

#include <stddef.h>

int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);

#endif