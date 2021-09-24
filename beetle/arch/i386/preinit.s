[BITS 32]
[CPU 386]
;The kernel will be loaded by GRUB.

%include "include/descriptor.s"

%define GDT_SIZE_IN_SEGMENTS 256
%define GDT_SIZE_IN_BYTES GDT_SIZE_IN_SEGMENTS * 8 - 1

extern kmain

global preinit
preinit:
	mov al, 0xFF
	out 0x21, al
	out 0xA1, al
	cli ;Disabling interrupts from the pick and disabling NMI before loading a new GDT for the kernel

	lgdt [gdtr]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	jmp 0x8:.next
	.next:

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ax, 0x18
	mov ss, ax
	mov esp, 0x7FB00

	call kmain

	.loop:
		cli
		hlt
		jmp .loop

section .data
gdtr:
	.limit: dw GDT_SIZE_IN_BYTES
	.base: dd gdt_start

;Interrupt vectors from the old vectors
;TODO: Maybe I don't want to overright the old vector in case I want to virtual 8086 mode
global idtr, idtSize, idtBase
idtSize: dw 0x499
idtBase: dd 0

idtr:
	.limit: dw 0x499
	.base: dd 0


section gdt
gdt_start: ;Will be aligned on 8bytes boundaries by the linker script
	dq 0;First entry in the GDT must be null
	DESCRIPTOR(0,0xFFFFF,CODE_EXECUTE_READ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
	DESCRIPTOR(0,0xFFFFF,DATA_READ_WRITE   ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
	DESCRIPTOR(0x600,0x7FAFF,DATA_READ_WRITE,PRESENT | PRIVILEDGE0,GRANULARITY_BYTE | SIZE32);stack from the low memory region on the available space : 0x500 to 0x7FFFF

	DESCRIPTOR(0,0xFFFFF,CODE_EXECUTE_READ,PRESENT | PRIVILEDGE3,GRANNULARITY_4K | SIZE32)
	DESCRIPTOR(0,0xFFFFF,DATA_READ_WRITE   ,PRESENT | PRIVILEDGE3,GRANNULARITY_4K | SIZE32)
