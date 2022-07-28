#include <stdint.h>
#include <string.h>
#include <beetle/arch.hpp>
#include "beetle/multiboot.hpp"
#include "elf/elf.h"
#include "vga_pc.hpp"

static VGA* vga = nullptr;

static void executeProcessManagement(const Elf32_Ehdr* const elf)
{
	const bool ident_ok = (elf->e_ident[EI_MAG0] == ELFMAG0) && (elf->e_ident[EI_MAG1] == ELFMAG1) && (elf->e_ident[EI_MAG2] == ELFMAG2) && (elf->e_ident[EI_MAG3] == ELFMAG3);

	if (!ident_ok) {
		vga->puts("[BEETLE]: ill formed process manager elf");
		return;
	}

	if (elf->e_ident[EI_CLASS] != ELFCLASS32) {
		vga->puts("[BEETLE]: only 32 bits elf can be executed");
		return;
	}

	
}

extern "C" int kmain (const uint32_t eax, const MultibootInformation* const multibootInfo)
{
	if (eax != 0x2BADB002)
		return -1;
	VGA vga;
	ARCH::init();
	vga.puts("[BEETLE]: succesfull load");

	/**
	 * Every capabilities of the operating system will be provided as services. The only purpose of the OS is
	 * to provide a way for different programs to communicate to the services. The first services to be launched is
	 * the process manager.
	 * 
	 * This services is loaded in RAM via the bootloader as at this stage, the OS has no way to fetch data from the
	 * connected drives.
	 */
	const MultibootModule* const multibootModules = (const MultibootModule* const)multibootInfo->mods_addr;
	int pmnMultibootPos = -1;

	if (!multibootInfo->flags & (1 << 3))
	{
		vga.puts("[ERROR]: The bootloader didn't provide loading executable capabilities. Beetle cannot get critical components. Cannot continue");
		goto boot_error;
	}

	if (multibootInfo->mods_count == 0)
	{
		vga.puts("[ERROR]: Critical components of Beetle not loaded by the bootloader. Cannot continue");
		goto boot_error;
	}

	for (int i = 0; i < multibootInfo->mods_count; ++i)
	{
		if (strcmp((const char*)multibootModules[i].mod_string, BEETLE_PMN_NAME) == 0) {
			pmnMultibootPos = i;
			break;
		}
	}

	if (pmnMultibootPos == -1)
	{
		vga.puts("[ERROR]: Cannot find process manager in memory. Boot aborted");
		goto boot_error;
	}

	executeProcessManagement((const Elf32_Ehdr*)multibootModules[pmnMultibootPos].mod_start);

	vga.puts("[ERROR]: Unable to boot");

	boot_error:
	ARCH::endlessLoop();
	return 0;
}
