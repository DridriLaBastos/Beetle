#include <ksys/ksys.h>

#include "arch/interface.h"

void kc_putchar (const int c)
{
	//Get current VGA cursor position
	const uint16_t cursorPosition = kinw(0x3D4);
	//Get the current VGA cursor position
	const uint16_t cursorOffset = cursorPosition & 0xFF;
	//Get the current VGA cursor page
	const uint16_t cursorPage = cursorPosition >> 8;

	//Output char to the VGA buffer
	koutw(c | (0x0F << 8), 0xB8000 + cursorOffset + cursorPage * 80 * 2);

	//Output new line if the cursor is at the end of the line
	if (cursorOffset == 79)
	{
		//Move the cursor to the beginning of the next line
		koutw(cursorPage << 8, 0x3D4);
		koutw(0, 0x3D5);
	}
	else
	{
		//Move the cursor to the next position
		koutw(cursorOffset + 1, 0x3D4);
		koutw(cursorPage, 0x3D5);
	}
}
