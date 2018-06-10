ENTRY(boot_stage_1_main)

SECTIONS
{
	. = 1M;
	
	.header : {
		*(.multiboot_header)
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