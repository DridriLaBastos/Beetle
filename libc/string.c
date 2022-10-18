#include <stdint.h>

#include "string.h"

int strcmp (const char* s1, const char* s2)
{
	int cmp = 0;

	do
	{
		cmp = *s1 - *s2;
		s1 += 1;
		s2 += 1;

	} while(*s1 && *s2 && !cmp);

	return cmp;
}