#include "beetle/include/system.hpp"

extern "C" void boot_stage_1_main (void)
{
	BEETLE::SYSTEM::init();
	asm("xchg %bx, %bx");
	//asm("sti");
	for(;;);
}