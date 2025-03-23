// Must be provided by the compiler
#include <stdarg.h>
#include <stdbool.h>

#include <kstdio.h>
#include <kstdlib.h>
#include <kstddef.h>

static int parsePrintfFlags(void) {
	return EXIT_FAILURE;
}

static int parsePrintfWidth(void) {
	return EXIT_FAILURE;
}

static int parsePrintfPrecision(void) {
	return EXIT_FAILURE;
}

static void PrintfPrintInteger10(unsigned int n)
{
	static char decStr [] = {
			'0','1','2','3','4','5','6','7','8','9'
	};

	char display[9];
	unsigned int nDigitFree = 9;

	if (n < 0)
	{
		kputchar('-');
	}

	do {
		nDigitFree -= 1;
		display[nDigitFree] = decStr[n % 10];
		n /= 10;
	} while (n > 0);

	for (size_t i = nDigitFree; i < 9; ++i){
		kputchar(display[i]);
	}
}

static void PrintfPrintInteger16(unsigned int n, const bool upperCase)
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
		kputchar(display[i]);
	}
}

static void PrintfPrintStr(const char* str)
{
	while(*str)
		kputchar(*str++);
}

static int ParsePrintfType(const char** c, va_list* args)
{
	int ret = EXIT_SUCCESS;
	switch(**c)
	{
		case 'i':
		case 'd':
		{
			const int argValue = va_arg(*args,int);
			PrintfPrintInteger10(argValue < 0 ? -argValue : argValue);
		} break;

		case 'u':
			PrintfPrintInteger10(va_arg(*args,unsigned int));
			break;

		case 'x':
			PrintfPrintInteger16(va_arg(*args,unsigned int),false);
			break;

		case 'X':
			PrintfPrintInteger16(va_arg(*args,unsigned int),true);
			break;

		case 's':
			PrintfPrintStr(va_arg(*args,char*));
			break;

		default:
			ret = EXIT_FAILURE;
			break;
	}
	return ret;
}

// Simple printf format specifier parser, only parses the type and only accept a small subset  of types
static int ParsePrintfFormatSpecifier(const char** format, va_list* args)
{
	//Only parse the type declaration part of printf
	return ParsePrintfType(format,args);
}

int kprintf(const char* format, ...)
{
	va_list args;

	va_start(args,format);
	unsigned int charWrittenCount = 0;
	for (const char* c = format; *c != '\0'; c += 1)
	{
		const char currentChar = *c;
		if (currentChar != '%')
		{ kputchar(currentChar); }
		else
		{
			c += 1;
			if (ParsePrintfFormatSpecifier(&c,&args))
			{
				kputchar(currentChar);
			}
		}
	}

	va_end(args);
	return (int)charWrittenCount;
}