#ifndef __MULTIBOOT_HPP__
#define __MULTIBOOT_HPP__

#include <stdint.h>

struct MultibootInformation {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmd_line;
	uint32_t mods_count;
	uint32_t mods_addr;
	union {
		uint32_t tabsize;
		uint32_t num;
	};
	union {
		uint32_t strsize;
		uint32_t size;
	};
	uint32_t addr;
	uint32_t shndx;
	uint32_t other [83];

} __attribute__((packed));

struct MultibootModule {
	const uint32_t mod_start;
	const uint32_t mod_end;
	const uint32_t mod_string;
	const uint32_t reserved;
} __attribute__((packed));

#endif