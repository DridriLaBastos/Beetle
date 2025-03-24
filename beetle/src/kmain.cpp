#include <stdio.h>

#include "beetle/arch.hpp"
#include "beetle/multiboot.hpp"
#include "beetle/elf/elf.h"

static void executeProcessManagement(const Elf32_Ehdr* const elf)
{
	const bool ident_ok = (elf->e_ident[EI_MAG0] == ELFMAG0) && (elf->e_ident[EI_MAG1] == ELFMAG1) && (elf->e_ident[EI_MAG2] == ELFMAG2) && (elf->e_ident[EI_MAG3] == ELFMAG3);

	if (!ident_ok) {
		kputs("[BEETLE]: ill formed process manager elf");
		return;
	}

	if (elf->e_ident[EI_CLASS] != ELFCLASS32) {
		kputs("[BEETLE]: only 32 bits elf can be executed");
		return;
	}
}

static void parseMultibootInfo(const MultibootInformation* const multibootInfo)
{
	kputs("[BEETLE]: scanning boot environment");
	const uint32_t multibootFlags = multibootInfo->flags;

	kprintf("[BEETLE]: multiboot flags : ");
	for (unsigned int i = 1 << 31; i != 0; i >>= 1)
	{ kputchar((i & multibootFlags) ? '1' : '0'); }
	kputchar('\n');


	if (multibootFlags & (1 << 0)) {
		kprintf("[BEETLE]: lower memory available : %dkb\n", multibootInfo->mem_lower);
		kprintf("[BEETLE]: upper memory available : %dmb\n", multibootInfo->mem_upper / 1024);
		kprintf("[BEETLE]: total memory available : %dmb\n", (multibootInfo->mem_lower + multibootInfo->mem_upper)/1024);
	}

	if (multibootFlags & (1 << 1)) {
		kprintf("[BEETLE]: boot device 0x%X\n", multibootInfo->boot_device);
	}

	if (multibootFlags & (1 << 2)){
		kprintf("[BEETLE]: kernel args '%s'\n",multibootInfo->cmd_line);
	}

	if (multibootFlags & (1 << 3)) {
		kprintf("[BEETLE]: %d submodule loaded\n",multibootInfo->mods_count);

		MultibootModule* modules = (MultibootModule*)multibootInfo->mods_addr;
		for (unsigned int i = 0; i < multibootInfo->mods_count; ++i) {
			kprintf(" * %d : '%s' at 0x%X\n",i,modules[i].mod_string, modules[i].mod_start);
		}
	}

	//The kernel exe has an elf file format, thus, because bit 4&5 are mutually exclusive
	//only bit 5, for elf, must be set : no need to test bit 4
	if (multibootFlags & (1 << 5)) {
		kprintf("[BEETLE]: kernel executable loaded at address 0x%X\n",multibootInfo->addr);
	}
}

extern "C" int kmain (const uint32_t eax, const MultibootInformation* const multibootInfo)
{
	if (eax != 0x2BADB002)
		return -1;

	kputs("[BEETLE]: successfully loaded");
	kputs("[ARCH]: starting low level initialization");
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

	MultibootModule* modules = (MultibootModule*)multibootInfo->mods_addr;

	if (modules) {
		Elf32_Ehdr* header = (Elf32_Ehdr*) modules[0].mod_start;
		ARCH::moveToUserLand(header->e_entry);
	}

	kputs("[BEETLE]: resumed");
	boot_error:
	ARCH::endlessLoop();
	return 0;
}
