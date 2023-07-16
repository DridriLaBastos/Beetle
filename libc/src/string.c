#include "../string.h"

#define CHAR_COMP(chptr1,chptr2) *(chptr1++) - *(chptr2++)

int strcmp (const char* s1, const char* s2)
{
	int cmp = 0;

	do
	{
		cmp = CHAR_COMP(s1,s2);
	} while(*s1 && *s2 && !cmp);

	return cmp;
}

int strncmp (const char* s1, const char* s2, size_t n)
{
	int cmp = 0;

	for (size_t i = 0; i < n && *s1 && *s2 && !cmp; ++i)
	{
		cmp = CHAR_COMP(s1,s2);
	}

	return cmp;
}

void* memset(void* dest, int value, size_t len)
{
	const unsigned char v = (unsigned char)value;

	for (size_t i = 0; i < len; i += 1)
	{ ((unsigned char*)dest)[i] = v; }
}
