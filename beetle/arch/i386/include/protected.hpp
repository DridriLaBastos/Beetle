#ifndef __PROTECTED_HPP__
#define __PROTECTED_HPP__

#include <stdint.h>

namespace ARCH::I386
{
	struct GDT
	{
		private: unsigned int mCount;
	};
}

namespace ARCH::I386::IDT
{
	void push (const uint64_t descriptor);
	void push (const uint64_t descriptor, const unsigned int n);
	void load (void);
}

#endif