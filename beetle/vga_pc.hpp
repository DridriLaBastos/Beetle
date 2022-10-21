#ifndef VGA_PC_HPP
#define VGA_PC_HPP

#include <stdint.h>

namespace VGA
{
	void putc (const int c);
	void puts (const char* const str);
};

#endif