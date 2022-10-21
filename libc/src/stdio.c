//
// Created by Adrien COURNAND on 21/10/2022.
//

#include <stdarg.h>
#include <stddef.h>

#include "../stdio.h"
#include "../stdlib.h"

#include "beetle/vga_pc_c_api.h"

int puts(const char* s)
{
	vga_pc_c_puts(s);
	return EXIT_SUCCESS;
}

int putc(const int c)
{
	vga_pc_c_putc(c);
	return EXIT_SUCCESS;
}

int printf(const char* format, ...)
{
	va_list args;

	va_start(args,format);

	for (char* c = format; *c != '\0'; c += 1)
	{
		const char currentChar = *c;
		if (currentChar != '%')
		{ vga_pc_c_putc(currentChar); }
	}


}
