[BITS 32]
[CPU 386]
;The kernel will be loaded by GRUB.

; %include "descriptor.s"

; %define GDT_SIZE_IN_SEGMENTS 256
; %define IDT_SIZE_IN_ENTRIES  256

; %define GDT_SIZE_IN_BYTES GDT_SIZE_IN_SEGMENTS * 8 - 1
; %define IDT_SIZE_IN_BYTES IDT_SIZE_IN_ENTRIES * 8 - 1

extern kmain,gdt,idt,gdtr,idtr

global preinit
preinit:
	mov edi, eax ;eax must contain a multiboot value put here by the loader. eax is saved to be passed to kmain
	mov esi, ebx ;edx contrains the address of the multiboot info data struct. edx is saved to be passed to kmain.

	mov al, 0xFF ;0xFF is the value to mask the interrupts on both PICs
	out 0x21, al ;masking interrupts on PIC 1 
	out 0xA1, al ;masking interrupts in PIC 2
	cli ;disabling nmi while switching to protected mode

	lgdt [gdtr] ;Loading the gdtr structur created in arch.cpp

	; passing into protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; Jumping to the first priviledged code segment
	jmp 0x8:.next
	.next:

	; Loading priviledge 0 data segment
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Loading priviledge 0 stack segment
	mov ax, 0x18
	mov ss, ax
	mov esp, 0x7FB00

	;Setting the stack frame for kmain
	; first args = saved value of eax
	; second rgs = savec value of ebx
	push esi
	push edi
	xchg bx,bx
	call kmain
	cli ;If ever we returns from kmain it means that something bad happened

	.loop:
		hlt
		jmp .loop

; section .data
; global gdt_current, idt_current, gdtr, idtr, gdt, idt

; gdt_current: dd 4
; idt_current: dd 0
; gdt: dd gdt_start
; idt: dd idt_start

; gdtr:
; 	.limit: dw GDT_SIZE_IN_BYTES
; 	.base: dd gdt_start

; idtr:
; 	.limit: dw IDT_SIZE_IN_BYTES
; 	.base: dd idt_start

; section gdt write qword
; gdt_start:
; 	dq 0;First entry in the GDT must be null
; 	DESCRIPTOR(0,0xFFFFF,CODE_EXECUTE_READ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
; 	DESCRIPTOR(0,0xFFFFF,DATA_READ_WRITE   ,PRESENT | PRIVILEDGE0,GRANNULARITY_4K | SIZE32)
; 	DESCRIPTOR(0x600,0x7FAFF,DATA_READ_WRITE,PRESENT | PRIVILEDGE0,GRANULARITY_BYTE | SIZE32);stack from the low memory region on the available space : 0x500 to 0x7FFFF (avoiding the old interrupt vectors from the BIOS)
; 	resq GDT_SIZE_IN_SEGMENTS - 5

; section idt write qword
; idt_start:
; 	resq IDT_SIZE_IN_ENTRIES
