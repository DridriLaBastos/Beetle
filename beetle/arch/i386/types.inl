#include <stdint.h>

#include "beetle/arch.hpp"

struct __attribute__((packed)) ARCH::ExecutionContext
{
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp;
    uint32_t ds, es, fs, gs;
    uint32_t eip, cs, eflags, esp, ss;
};