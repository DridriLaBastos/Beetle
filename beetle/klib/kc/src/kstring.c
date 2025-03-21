#include "kstring.h"

void* kmemset(void* dest, int c, size_t len)
{
	char* d = (char*)dest;
	while (len--)
	{
		*(char*)d = (char)c;
		d += 1;
	}

	return dest;
}