ENTRY(preinit)

SECTIONS
{
	. = 1M;
	
	.header ALIGN(4K) : {
		*(multiboot_header)
	}

	.text : {
		*(.text)
	}

	.data : {
		*(.data)
	}

	.rodata : {
		*(.rodata)
	}

	.bss : {
		*(.bss)
		*(COMMON)
	}

	.gdt ALIGN(8) : {
		*(gdt)
	}
}