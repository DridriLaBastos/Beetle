#include <ksys/ksys.h>

void koutb (const uint8_t value, const unsigned int addr)
{ asm ("outb %0, %1":: "a" (value), "dx" (addr)); }
void koutw (const uint16_t value, const unsigned int addr)
{ asm ("outw %0, %1":: "a" (value), "dx" (addr)); }
void koutd (const uint32_t value, const unsigned int addr)
{ koutw (value & 0xFFFF, addr); koutw (value >> 16, addr + 2); }

uint8_t kinb (const unsigned int addr)
{
	uint8_t result = 0;
	asm ("inb %1, %0" : "=a" (result) : "dx" (addr));
	return result;
}

uint16_t kinw (const unsigned int addr)
{
	uint16_t result = 0;
	asm ("inw %1, %0" : "=a" (result) : "dx" (addr));
	return result;
}

uint32_t kind (const unsigned int addr)
{
	return kinw(addr) | (kinw(addr + 2) << 16);
}
