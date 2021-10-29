#include <stdint.h>
#include <beetle/arch.hpp>
#include "vga_pc.hpp"

extern "C" int kmain (const uint32_t eax, const uint32_t* multibootInfo)
{
	if (eax != 0x2BADB002)
		return -1;
	VGA vga;
	ARCH::init();
	vga.puts("[BEETLE]: succesfull load");
	ARCH::endlessLoop();
	return 0;
}