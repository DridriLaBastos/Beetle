#include <beetle/arch.hpp>
#include "vga_pc.hpp"

extern "C" int kmain (void)
{
	VGA vga;
	ARCH::init();
	vga.puts("[BEETLE]: succesfull load");
	ARCH::endlessLoop();
	return 0;
}