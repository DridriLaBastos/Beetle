#include "beetle/include/system.hpp"

extern "C" void boot_stage_1_main (void)
{
	BEETLE::SYSTEM::init();
	dest: 
	goto dest;
}