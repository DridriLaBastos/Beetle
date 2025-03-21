#ifndef KERNEL_STRING_H
#define KERNEL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "kstddef.h"

void* kmemset(void* dest, int c, size_t len);

#ifdef __cplusplus
}
#endif

#endif