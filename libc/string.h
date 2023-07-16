#ifndef __BEETLE_LIBC_STRING_H__
#define __BEETLE_LIBC_STRING_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

void* memset(void* dest, int value, size_t len);

#ifdef __cplusplus
};
#endif

#endif