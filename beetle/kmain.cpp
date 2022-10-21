#include <stdio.h>

#include <beetle/arch.hpp>
#include "beetle/multiboot.hpp"
#include "elf/elf.h"

static void executeProcessManagement(const Elf32_Ehdr* const elf)
{
	const bool ident_ok = (elf->e_ident[EI_MAG0] == ELFMAG0) && (elf->e_ident[EI_MAG1] == ELFMAG1) && (elf->e_ident[EI_MAG2] == ELFMAG2) && (elf->e_ident[EI_MAG3] == ELFMAG3);

	if (!ident_ok) {
		puts("[BEETLE]: ill formed process manager elf");
		return;
	}

	if (elf->e_ident[EI_CLASS] != ELFCLASS32) {
		puts("[BEETLE]: only 32 bits elf can be executed");
		return;
	}
}

static void parseMultibootInfo(const MultibootInformation* const multibootInfo)
{
	puts("[BEETLE]: scanning boot environment");
	const uint32_t multibootFlags = multibootInfo->flags;
}

extern "C" int kmain (const uint32_t eax, const MultibootInformation* const multibootInfo)
{
	if (eax != 0x2BADB002)
		return -1;

	puts("[BEETLE]: successfully loaded");
	puts("[ARCH]: starting low level initialization");
	ARCH::init();

	/**
	 * Every capabilities of the operating system will be provided as services. The only purpose of the OS is
	 * to provide a way for different programs to communicate to the services. The first services to be launched is
	 * the process manager.
	 * 
	 * This services is loaded in RAM via the bootloader as at this stage, the OS has no way to fetch data from the
	 * connected drives.
	 */
	parseMultibootInfo(multibootInfo);
	boot_error:
	ARCH::endlessLoop();
	return 0;
}
