//
// Created by Adrien COURNAND on 21/10/2022.
//

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#include "../stdio.h"
#include "../stdlib.h"

#include "beetle/vga_pc_c_api.h"

static unsigned int printfCharWriten = 0;

int puts(const char* s)
{
	vga_pc_c_puts(s);
	return EXIT_SUCCESS;
}

int putchar (const int c)
{
	vga_pc_c_putc(c);
	printfCharWriten += 1;
	return EXIT_SUCCESS;
}

static int parsePrintfFlags(void) {
	return 0;
}

static int parsePrintfWidth(void) {
	return 0;
}

static int parsePrintfPrecision(void) {

}

static void printfPrintInteger10(unsigned int n)
{
	static char decStr [] = {
			'0','1','2','3','4','5','6','7','8','9'
	};

	char display[9];
	unsigned int nDigitFree = 9;
	do {
		nDigitFree -= 1;
		display[nDigitFree] = decStr[n % 10];
		n /= 10;
	} while (n > 0);

	for (size_t i = nDigitFree; i < 9; ++i){
		putchar(display[i]);
	}
}

static void printfPrintInteger16(unsigned int n, const bool upperCase)
{
	static char hexChar [] = {
			'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
	};

	hexChar[0xA] = upperCase ? 'A' : 'a';
	hexChar[0xB] = upperCase ? 'B' : 'b';
	hexChar[0xC] = upperCase ? 'C' : 'c';
	hexChar[0xD] = upperCase ? 'D' : 'd';
	hexChar[0xE] = upperCase ? 'E' : 'e';
	hexChar[0xF] = upperCase ? 'F' : 'f';

	char display [8];
	unsigned int nDigitFree = 8;

	do {
		nDigitFree -= 1;
		display[nDigitFree] = hexChar[n & 0xF];
		n >>= 4;
	} while (n > 0);

	//TODO: Idea of optimization : using a switch to unroll the loop
	for (size_t i = nDigitFree; i < 8; ++i)
	{
		putchar(display[i]);
	}
}

static void printfPrintStr(const char* str)
{
	while(*str)
		putchar(*str++);
}

static int parsePrintfSpecifier(const char** c, va_list* args)
{
	int ret = EXIT_SUCCESS;
	switch(**c)
	{
		case 'i':
		case 'd':
		{
			const int argValue = va_arg(*args,int);
			if (argValue < 0)
				putchar('-');
			printfPrintInteger10(argValue < 0 ? -argValue : argValue);
		} break;

		case 'u':
			printfPrintInteger10(va_arg(*args,unsigned int));
			break;

		case 'x':
			printfPrintInteger16(va_arg(*args,unsigned int),false);
			break;

		case 'X':
			printfPrintInteger16(va_arg(*args,unsigned int),true);
			break;

		case 's':
			printfPrintStr(va_arg(*args,char*));
			break;

		default:
			ret = EXIT_FAILURE;
			break;
	}
	return ret;
}

static void parsePrintfArgs(const char** format, va_list* args)
{
	//Only parse the type declaration part of printf
	parsePrintfSpecifier(format,args);
}

int printf(const char* format, ...)
{
	va_list args;

	va_start(args,format);
	printfCharWriten = 0;
	for (const char* c = format; *c != '\0'; c += 1)
	{
		const char currentChar = *c;
		if (currentChar != '%')
		{ putchar(currentChar); }
		else
		{
			c += 1;
			parsePrintfArgs(&c,&args);
		}
	}

	va_end(args);
	return (int)printfCharWriten;
}
