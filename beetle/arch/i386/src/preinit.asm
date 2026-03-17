[BITS 32]
[CPU 386]
;The kernel will be loaded by GRUB.

extern kmain,gdt,idt,gdtr,idtr,PrepareProtected

global preinit
preinit:
	mov edi, eax ;eax must contain a multiboot value put here by the loader. eax is saved to be passed to kmain
	mov esi, ebx ;ebx contrains the address of the multiboot info data struct. ebx is saved to be passed to kmain.

	mov al, 0xFF ;0xFF is the value to mask the interrupts on both PICs
	out 0x21, al ;masking interrupts on PIC 1 
	out 0xA1, al ;masking interrupts in PIC 2
	cli ;disabling nmi while switching to protected mode

	push kernel_stack.end - kernel_stack
	push kernel_stack
	call PrepareProtected

	lgdt [gdtr] ;Loading the gdtr structure created in arch.cpp
	lidt [idtr] ;Loading the idtr structure created in arch.cpp

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
	mov esp, kernel_stack.end - kernel_stack

	;Setting the stack frame for kmain
	; first args = saved value of eax
	; second args = saved value of ebx
	push esi
	push edi
	call kmain

	cli ;If ever we returns from kmain it means that something bad happened

	.loop:
		hlt
		jmp .loop

section .bss
; Kernel stack : saving 1024 uint32_T entries.
; The work of making the memory of this region available in the segment descriptor used by
kernel_stack:
resd 1024 
.end: