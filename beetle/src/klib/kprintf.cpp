#include <stdarg.h>

#include "beetle/arch.hpp"

static int ParseInt10(int d)
{
    char r [10] = {0,0,0,0,0,0,0,0,0,0};
    unsigned int length = 0;

    if (d < 0)
    {
        ARCH::DebugOutput('-');
        d = -d;
    }

    do
    {
        const int m = d % 10;
        d /= 10;
        r[length++] = m + '0';
    } while (d != 0);

    for (int i = length-1; i >= 0; i--)
    {
        ARCH::DebugOutput(r[i]);
    }

    return length;
}

static void ParseArgs (const char** fmtptr, va_list* args)
{
    const char specifier = *((*fmtptr)++);

    switch (specifier)
    {
        case 'd':
            ParseInt10(va_arg(*args,int));

        default:
            ARCH::DebugOutput(specifier);
    }
}

int kprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args,fmt);
    for (char c = *fmt; *fmt; c = *(++fmt))
    {
        if (c == '%')
        {
            ++fmt;
            ParseArgs(&fmt, &args);
        }
        else
        {
            ARCH::DebugOutput(c);
        }
    }

    va_end(args);

    return 0;
}