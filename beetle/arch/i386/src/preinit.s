[BITS 32]
[CPU 386]
;The kernel will be loaded by GRUB.

extern kmain,gdt,idt,gdtr,idtr

global preinit
preinit:
	mov edi, eax ;eax must contain a multiboot value put here by the loader. eax is saved to be passed to kmain
	mov esi, ebx ;edx contrains the address of the multiboot info data struct. edx is saved to be passed to kmain.

	mov al, 0xFF ;0xFF is the value to mask the interrupts on both PICs
	out 0x21, al ;masking interrupts on PIC 1 
	out 0xA1, al ;masking interrupts in PIC 2
	cli ;disabling nmi while switching to protected mode

	lgdt [gdtr] ;Loading the gdtr structure created in arch.cpp

	; passing into protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	; Jumping to the kernel code segment. This segment is the first usable in the gdt
	; it is placed at pos gdt[1] because the first segment must be null. This segment
	; is of priviledge 0 so the segment selector can only have a privilege level of 0.
	; this results in segment selector of 8
	jmp 0x8:.next
	.next:

	; Loading privilege 0 data segment
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;Loading privilege 0 stack segment
	mov ax, 0x18
	mov ss, ax
	mov esp, 0x7FB00

	;Setting the stack frame for kmain
	; first args = saved value of eax
	; second rgs = savec value of ebx
	push esi
	push edi
	call kmain
	cli ;If ever we returns from kmain it means that something bad happened

	.loop:
		hlt
		jmp .loop

