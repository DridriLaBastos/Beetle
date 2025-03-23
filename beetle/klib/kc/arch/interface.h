#ifndef ARCH_INTERFACE_H
#define ARCH_INTERFACE_H

#include "klib_util.h"

CPP_SCOPE_ENTER()

void kc_putchar (const int c);
void kc_cursor_update (void);

CPP_SCOPE_EXIT()

#endif
