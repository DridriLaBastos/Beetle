#include <stdint.h>

#include "string.h"

int strcmp (const char* s1, const char* s2)
{
	const uint8_t* o1 = s1;
	const uint8_t* o2 = s2;

	int cmp = 0;

	do
	{
		cmp = *o1 - *o2;
		o1 += 1;
		o2 += 1;

	} while(*o1 && *o2 && !cmp);

	return cmp;
}