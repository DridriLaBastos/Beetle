#ifndef __PORT_HPP__
#define __PORT_HPP__

#include <stdint.h>

extern "C"
{
	//The attibute regparm(2) causes gcc to pass the first parameter of the function in eax and the second in edx. Tis is what we want for out function because the instructions have the form 'out accumulator, dx', so we want to have the value to out in ax and the addres in dx
	__attribute__ ((regparm(2))) void outb (const uint8_t value, const unsigned int addr);
	__attribute__ ((regparm(2))) void outw (const uint16_t value, const unsigned int addr);
	__attribute__ ((regparm(2))) void outd (const uint32_t value, const unsigned int addr);

	//The atribute fastcall causes gcc to pass the first parameter of the funtion in edx. This makes sense because the in instruction have the form 'in accumulator, dx' so we want to have the addr in dx
	__attribute__((fastcall)) uint8_t inb (const unsigned int addr);
	__attribute__((fastcall)) uint16_t inw (const unsigned int addr);
	__attribute__((fastcall)) uint32_t ind (const unsigned int addr);
}

#endif