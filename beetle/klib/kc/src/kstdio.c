#include "kstdio.h"
#include "arch/interface.h"

#include <stdarg.h>

int putchar (const int c)
{
	kc_putchar(c);
	return 1;
}

int puts (const char* s)
{
	unsigned int accumulate = 0;
	while (*s)
	{
		putchar(*s);
		++accumulate;
		++s;
	}

	return accumulate;
}
