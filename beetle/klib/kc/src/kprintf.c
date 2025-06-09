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

static int PrintfPrintInteger10(int n)
{
	static char decStr [] = {
			'0','1','2','3','4','5','6','7','8','9'
	};

	char display[9];
	unsigned int nDigitFree = 9;
	int charWrittenCount = 0;

	if (n < 0)
	{
		kputchar('-');
		charWrittenCount += 1;
	}

	do {
		nDigitFree -= 1;
		display[nDigitFree] = decStr[n % 10];
		n /= 10;
	} while (n > 0);

	for (size_t i = nDigitFree; i < 9; ++i){
		kputchar(display[i]);
		charWrittenCount += 1;
	}

	return charWrittenCount;
}

static int PrintfPrintInteger16(unsigned int n, const bool upperCase)
{
	static char hexChar [] = {
			'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
	};

	int charWrittenCount = 0;

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
		charWrittenCount += 1;
	}

	return charWrittenCount;
}

static int PrintfPrintStr(const char* str)
{
	const char* currentStrChar = str;
	while(*currentStrChar)
		kputchar(*currentStrChar++);
	
	return currentStrChar - str;
}

static int PrintfPrintChar(const char c)
{
	kputchar(c);
	return 1;
}

static int ParsePrintfType(const char* const format, va_list* args)
{
	int charWrittenCount = 0;
	switch(*format)
	{
		case 'i':
		case 'd':
			return PrintfPrintInteger10(va_arg(*args,int));

		case 'u':
			return PrintfPrintInteger10(va_arg(*args,unsigned int));

		case 'x':
			return PrintfPrintInteger16(va_arg(*args,unsigned int),false);

		case 'X':
			return PrintfPrintInteger16(va_arg(*args,unsigned int),true);

		case 's':
			return PrintfPrintStr(va_arg(*args,char*));
		
		case 'c':
			return PrintfPrintChar((char)va_arg(*args,int));

		default:
			break;
	}

	return 0;
}

// Simple printf format specifier parser, only parses the type and only accept a small subset  of types
static int ParsePrintfFormatSpecifier(const char* const format, va_list* args)
{
	//Only parse the type declaration part of printf
	return ParsePrintfType(format,args);
}

int kprintf(const char* format, ...)
{
	va_list args;

	va_start(args,format);
	unsigned int charWrittenCount = 0;
	for (; *format != '\0'; format += 1)
	{
		const char currentChar = *format;
		if (currentChar != '%')
		{
			kputchar(currentChar);
			charWrittenCount += 1;
		}
		else
		{
			format += 1; //Skip the '%' as it has already been processed
			if (*format != '\0')
			{
				charWrittenCount += ParsePrintfFormatSpecifier(format,&args);
			}
		}
	}

	va_end(args);
	return (int)charWrittenCount;
}