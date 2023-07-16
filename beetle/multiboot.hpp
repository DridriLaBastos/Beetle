#ifndef __MULTIBOOT_HPP__
#define __MULTIBOOT_HPP__

#include <stdint.h>

struct MultibootInformation {
	const uint32_t flags;
	const uint32_t mem_lower;
	const uint32_t mem_upper;
	const uint32_t boot_device;
	const uint32_t cmd_line;
	const uint32_t mods_count;
	const uint32_t mods_addr;
	const union {
		const uint32_t tabsize;
		const uint32_t num;
	};
	union {
		const uint32_t strsize;
		const uint32_t size;
	};
	const uint32_t addr;
	const uint32_t shndx;
	const uint32_t other [83];
} __attribute__((packed));

struct MultibootModule {
	const uint32_t mod_start;
	const uint32_t mod_end;
	const uint32_t mod_string;
	const uint32_t reserved;
} __attribute__((packed));

#endif