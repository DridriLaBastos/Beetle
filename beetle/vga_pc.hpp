#ifndef VGA_PC_HPP
#define VGA_PC_HPP

#include <stdint.h>

class VGA
{
	public:
		VGA(void);

		void putc (const char c);
		void puts (const char* const str);

	private:
		volatile uint16_t* m_vgaRam;
		unsigned int m_vgaBufferPosX;
		unsigned int m_vgaBufferPosY;
};

#endif