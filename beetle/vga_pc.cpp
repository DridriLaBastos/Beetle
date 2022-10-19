#include <stddef.h>

#include "vga_pc.hpp"

static constexpr unsigned int VGA_SCREEN_SIZE_X = 80;
static constexpr unsigned int VGA_SCREEN_SIZE_Y = 25;

static uint16_t* vgaRam = (uint16_t*)0xB8000;
static size_t vgaBufferPosX = 0;
static size_t vgaBufferPosY = 0;

void VGA::putc(const char c)
{
	if (c == '\n')
		vgaBufferPosX = VGA_SCREEN_SIZE_X;
	else if (c == '\t')
		vgaBufferPosX += 4;
	else
	{
		const uint8_t charToWrite = c;
		const uint8_t color 		= 0b100;
		const uint16_t valueToWrite = (color << 8) | charToWrite;
		vgaRam[vgaBufferPosY*VGA_SCREEN_SIZE_X + vgaBufferPosX++] = valueToWrite;
	}

	vgaBufferPosY += vgaBufferPosX / VGA_SCREEN_SIZE_X;
	vgaBufferPosX %= VGA_SCREEN_SIZE_X;
}

void VGA::puts(const char* const str)
{
	const char* tmp = str;
	while (*tmp != '\0')
		putc(*tmp++);
	putc('\n');
}
