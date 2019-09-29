ENTRY(main)

SECTIONS
{
	. = 1M;
	
	.header ALIGN(4K) : {
		*(.multiboot_header)
		*(.interrupt)
	}

	.text : {
		*(.text)
		*(.end)
	}

	.data : {
		*(.data)
	}

	.rodata : {
		*(.rodata)
	}

	.bss : {
		*(.bss)
	}
}