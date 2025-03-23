#ifndef KERNEL_SYS_H
#define KERNEL_SYS_H

#include <stdint.h>

#include "klib_util.h"

CPP_SCOPE_ENTER()

void koutb (const uint8_t value, const unsigned int addr);
void koutw (const uint16_t value, const unsigned int addr);
void koutd (const uint32_t value, const unsigned int addr);

uint8_t kinb (const unsigned int addr);
uint16_t kinw (const unsigned int addr);
uint32_t kind (const unsigned int addr);

CPP_SCOPE_EXIT()

#endif
