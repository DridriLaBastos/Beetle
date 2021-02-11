#ifndef BEETLE_SERVICES_HPP
#define BEETLE_SERVICES_HPP

#include <stdint.h>

/** 
 * This file contains all the functions that should be implemented to port the OS a new architecture.
 * The functions are declared with fastcall in order to be as fast as possible. fastcall is a gcc feature
 * and it may not change anything if it is not supported on a target.
 * 
 * On x86_32 target it permits to give arguments via registers
 */

extern "C"
{
	void __attribute__((fastcall)) outb (const uint8_t data, const unsigned int portNumber);
	void __attribute__((fastcall)) outw (const uint16_t data, const unsigned int portNumber);
	void __attribute__((fastcall)) outd (const uint32_t data, const unsigned int portNumber);

	uint8_t __attribute__((fastcall)) inb (const unsigned int portNumber);
	uint16_t __attribute__((fastcall)) inw (const unsigned int portNumber);
	uint32_t __attribute__((fastcall)) ind (const unsigned int portNumber);

	int initCpu (void* args);
}
#endif