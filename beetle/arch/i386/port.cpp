#include "include/port.hpp"

void outb (const uint8_t value, const unsigned int addr) { asm ("out %al ,%dx"); }
void outw (const uint16_t value, const unsigned int addr) { asm ("out %ax ,%dx"); }
void outd (const uint32_t value, const unsigned int addr) { asm ("out %eax ,%dx"); }

uint8_t inb (const unsigned int addr)
{
	asm ("xor %eax, %eax");
	asm ("in %dx, %al");
}

uint16_t inw (const unsigned int addr)
{
	asm ("xor %eax, %eax");
	asm ("in %dx, %ax");
}

uint32_t ind (const unsigned int addr)
{
	asm ("xor %eax, %eax");
	asm ("in %dx, %eax");
}
