#include "beetle/klib.hpp"
#include "beetle/arch.hpp"

int kprintf(const char* fmt, ...)
{
    for (char c = *fmt; *fmt; c = *(++fmt))
    {
        ARCH::DebugOutput(c);
    }
}