#include <stdint.h>
#include <beetle/arch.hpp>
#include "beetle/multiboot.hpp"
#include "vga_pc.hpp"

extern "C" int kmain (const uint32_t eax, const MultibootInformation* const multibootInfo)
{
	if (eax != 0x2BADB002)
		return -1;
	VGA vga;
	ARCH::init();
	vga.puts("[BEETLE]: succesfull load");

	if (!multibootInfo->flags & (1 << 3))
	{
		vga.puts("[ERROR]: The bootloader didn't provide loading executable capabilities. Beetle cannot get critical components. Cannot continue");
		goto boot_error;
	}

	/**
	 * All capabilities of the operating system will be provided as services. The only purpose of the OS will be
	 * to provide a way for different program to communicate to the services. The first services to be launched is
	 * the process manager.
	 * 
	 * This services is loaded in RAM via the bootloader as at this stage, the OS has no way to fetch data from the
	 * connected drives
	 */
	if (multibootInfo->mods_count == 0)
	{
		vga.puts("[ERROR]: Critical components of Beetle not loaded by the bootloader. Cannot continue");
		goto boot_error;
	}

	vga.puts("[INFO]: Jumping to process management");

	boot_error:
	ARCH::endlessLoop();
	return 0;
}