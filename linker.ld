SECTIONS
{
	. = 1M;
	
	.header : {
		*(.multiboot_header)
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
	}
}