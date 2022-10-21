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

	printf("[BEETLE]: multiboot flags : ");
	for (unsigned int i = 1 << 31; i != 0; i >>= 1)
	{ putchar((i & multibootFlags) ? '1' : '0'); }
	putchar('\n');

	if (multibootFlags & (1 << 0)) {
		printf("[BEETLE]: available memory: 0x%X to 0x%X\n", multibootInfo->mem_lower, multibootInfo->mem_upper);
	}

	if (multibootFlags & (1 << 1)) {
		printf("[BEETLE]: boot device 0x%X\n", multibootInfo->boot_device);
	}

	if (multibootFlags & (1 << 2)){
		printf("[BEETLE]: kernel args '%s'\n",multibootInfo->cmd_line);
	}

	if (multibootFlags & (1 << 3)) {
		printf("[BEETLE]: %d submodule loaded\n",multibootInfo->mods_count);
		printf("          load address : 0x%x\n",multibootInfo->mods_addr);
	}

	//The kernel exe has an elf file format, thus, because bit 4&5 are mutually exclusive
	//only bit 5, for elf, must be set : no need to test bit 4
	if (multibootFlags & (1 << 5)) {
		printf("[BEETLE]: kernel executable loaded at address 0x%X\n",multibootInfo->addr);
	}
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
