#ifndef KERNEL_STRING_H
#define KERNEL_STRING_H

#include "kstddef.h"

#ifdef __cplusplus
extern "C" {
#endif

void* kmemset(void* dest, int c, size_t len);

#ifdef __cplusplus
}
#endif

#endif