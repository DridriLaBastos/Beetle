#ifndef BEETLE_SERVICES_HPP
#define BEETLE_SERVICES_HPP

#include <stdint.h>

extern "C"
{
	void __attribute__((fastcall)) outb (const uint8_t data, const unsigned int portNumber);
	void __attribute__((fastcall)) outw (const uint16_t data, const unsigned int portNumber);
	void __attribute__((fastcall)) outd (const uint32_t data, const unsigned int portNumber);

	uint8_t __attribute__((fastcall)) inb (const unsigned int portNumber);
	uint16_t __attribute__((fastcall)) inw (const unsigned int portNumber);
	uint32_t __attribute__((fastcall)) ind (const unsigned int portNumber);
}
#endif