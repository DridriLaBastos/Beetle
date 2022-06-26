/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

int test_strcmp (const char* s1, const char* s2)
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

int main()
{
	const char* a = "bonjour";
	const char* b = "cccccc";
    printf("test: %d   real: %d\n",test_strcmp(a,b), strcmp(a,b));

    return 0;
}
