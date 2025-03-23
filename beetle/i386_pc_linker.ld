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

	.idt ALIGN(8) : {
		*(idt)
	}

	.gdt ALIGN(8) : {
		*(gdt)
	}
}