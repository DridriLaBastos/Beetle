#include "vga_pc.hpp"

static constexpr unsigned int VGA_SCREEN_SIZE_X = 80;
static constexpr unsigned int VGA_SCREEN_SIZE_Y = 25;

VGA::VGA(): m_vgaRam((uint16_t*)0xB8000), m_vgaBufferPosX(0), m_vgaBufferPosY(0)
{
}

void VGA::putc(const char c)
{
	if (c == '\n')
		m_vgaBufferPosX = VGA_SCREEN_SIZE_X;
	else if (c == '\t')
		m_vgaBufferPosX += 4;
	else
	{
		const uint8_t charToWrite = c;
		const uint8_t color 		= 0b100;
		const uint16_t valueToWrite = (color << 8) | charToWrite;
		m_vgaRam[m_vgaBufferPosY*VGA_SCREEN_SIZE_X + m_vgaBufferPosX++] = valueToWrite;
	}

	m_vgaBufferPosY += m_vgaBufferPosX / VGA_SCREEN_SIZE_X;
	m_vgaBufferPosX %= VGA_SCREEN_SIZE_X;
}

void VGA::puts(const char* const str)
{
	const char* tmp = str;
	while (*tmp != '\0')
		putc(*tmp++);
}