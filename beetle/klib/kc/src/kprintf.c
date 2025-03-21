#include <stdarg.h>

#include "kstdio.h"

int printf(const char* format, ...)
{
	va_list args;

	va_start(args,format);
	unsigned int charWrittenCount = 0;
	// for (const char* c = format; *c != '\0'; c += 1)
	// {
	// 	const char currentChar = *c;
	// 	if (currentChar != '%')
	// 	{ putchar(currentChar); }
	// 	else
	// 	{
	// 		c += 1;
	// 		parsePrintfArgs(&c,&args);
	// 	}
	// }

	va_end(args);
	return (int)charWrittenCount;
}