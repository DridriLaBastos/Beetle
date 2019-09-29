#ifndef IO_HPP
#define IO_HPP

#include <stdint.h>

namespace ARCH {namespace I386 {namespace IO
{
	//I just like using unsigned int for data, I have no reasons why
	void outB (const unsigned int data, const unsigned int portNumber);
	void outW (const unsigned int data, const unsigned int portNumber);
	void outD (const unsigned int data, const unsigned int portNumber);

	unsigned int inB (const unsigned int portNumber);
	unsigned int inW (const unsigned int portNumber);
	unsigned int inD (const unsigned int portNumber);
}}}

#endif