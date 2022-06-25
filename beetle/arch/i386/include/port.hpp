#ifndef __PORT_HPP__
#define __PORT_HPP__

#include <stdint.h>

namespace ARCH::I386
{
	static inline void outb (const uint8_t value, const uint16_t addr)
	{ asm ("outb %0, %1":: "a" (value), "dx" (addr)); }
	static inline void outw (const uint16_t value, const uint16_t addr)
	{ asm ("outw %0, %1":: "a" (value), "dx" (addr)); }
	static inline void outd (const uint32_t value, const uint16_t addr)
	{ asm ("outd %0, %1":: "a" (value), "dx" (addr)); }

	static inline uint8_t inb (const uint16_t addr)
	{
		uint8_t result = 0;
		asm ("inb %1, %0" : "=a" (result) : "dx" (addr));
		return result;
	}

	static inline uint16_t inw (const uint16_t addr)
	{
		uint16_t result = 0;
		asm ("inw %1, %0" : "=a" (result) : "dx" (addr));
		return result;
	}

	static inline uint32_t ind (const uint16_t addr)
	{
		uint32_t result = 0;
		asm ("ind %1, %0" : "=a" (result) : "dx" (addr));
		return result;
	}
}

#endif