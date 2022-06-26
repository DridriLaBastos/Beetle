[BITS 32]
[CPU 386]
;The kernel will be loaded by GRUB.

%include "descriptor.s"

%define GDT_SIZE_IN_SEGMENTS 256
%define IDT_SIZE_IN_ENTRIES  256

%define GDT_SIZE_IN_BYTES GDT_SIZE_IN_SEGMENTS * 8 - 1
%define IDT_SIZE_IN_BYTES IDT_SIZE_IN_ENTRIES * 8 - 1

extern kmain

global preinit
preinit:
	xchg bx, bx
	mov edi, eax ;Saving the value of eax it will be passed to stack for kmain to verify that the bootloard is multiboot compliant
	mov esi, ebx ;Saving the value of ebx : it will contain the address of the multiboot info datastructur

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

	;Setting the stack frame for kmain
	; first args = saved value of eax
	; second rgs = savec value of ebx
	push esi
	push edi
	xchg bx, bx
	call kmain
	cli ;If ever we returns from kmain it means that something bad happened

	.loop:
		hlt
		jmp .loop

section .data
global gdt_current, idt_current, gdtr, idtr, gdt, idt

gdt_current: dd 4
idt_current: dd 0
gdt: dd gdt_start
idt: dd idt_start

gdtr:
	.limit: dw GDT_SIZE_IN_BYTES
	.base: dd gdt_start

idtr:
	.limit: dw IDT_SIZE_IN_BYTES
	.base: dd idt_start

section gdt write qword
gdt_start:
	dq 0;First entry in the GDT must be null
	DESCRIPTOR(0,0xFFFFF,CODE_EXECUTE_READ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
	DESCRIPTOR(0,0xFFFFF,DATA_READ_WRITE   ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
	DESCRIPTOR(0x600,0x7FAFF,DATA_READ_WRITE,PRESENT | PRIVILEDGE0,GRANULARITY_BYTE | SIZE32);stack from the low memory region on the available space : 0x500 to 0x7FFFF (avoiding the old interrupt vectors from the BIOS)
	resq GDT_SIZE_IN_SEGMENTS - 4

section idt write qword
idt_start:
	resq IDT_SIZE_IN_ENTRIES
