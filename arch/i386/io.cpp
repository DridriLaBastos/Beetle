#include "io.hpp"

extern "C"
{
	void __attribute__((fastcall)) outb (const unsigned int data, const unsigned int portNumber);
	void __attribute__((fastcall)) outw (const unsigned int data, const unsigned int portNumber);
	void __attribute__((fastcall)) outd (const unsigned int data, const unsigned int portNumber);

	unsigned int __attribute__((fastcall)) inb (const unsigned int portNumber);
	unsigned int __attribute__((fastcall)) inw (const unsigned int portNumber);
	unsigned int __attribute__((fastcall)) ind (const unsigned int portNumber);
}

void ARCH::I386::IO::outB(const unsigned int data, const unsigned int portNumber) { outb(data,portNumber); }
void ARCH::I386::IO::outW(const unsigned int data, const unsigned int portNumber) { outw(data,portNumber); }
void ARCH::I386::IO::outD(const unsigned int data, const unsigned int portNumber) { outd(data,portNumber); }

unsigned int ARCH::I386::IO::inB(const unsigned int portNumber) { return inb(portNumber); }
unsigned int ARCH::I386::IO::inW(const unsigned int portNumber) { return inw(portNumber); }
unsigned int ARCH::I386::IO::inD(const unsigned int portNumber) { return ind(portNumber); }