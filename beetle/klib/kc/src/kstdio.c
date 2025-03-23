#include "kstdio.h"
#include "arch/interface.h"

#include <stdarg.h>

int kputchar (const int c)
{
	kc_putchar(c);
	return 1;
}

int kputs (const char* s)
{
	unsigned int accumulate = 0;
	while (*s)
	{
		kputchar(*s);
		++accumulate;
		++s;
	}

	return accumulate;
}
