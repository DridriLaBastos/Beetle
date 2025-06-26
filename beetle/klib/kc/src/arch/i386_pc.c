#include <kstddef.h>

#include <ksys/ksys.h>

#include "arch/interface.h"

#define VGA_SCREEN_SIZE_X 80
#define VGA_SCREEN_SIZE_Y 25

static uint16_t* vgaRam = (uint16_t*)0xB8000;
static size_t vgaBufferPosX = 0;
static size_t vgaBufferPosY = 0;

static void OutputByteToCom1 (const uint8_t value)
{
	// Wait for the transmit buffer to be empty
	while ((kinb(0x3F8 + 5) & 0x20) == 0);
	koutb(value, 0x3F8);
}

void kc_putchar (const int c)
{
	OutputByteToCom1(c);
}

void kc_cursor_update()
{
	
}
