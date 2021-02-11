extern init
global main

;Before anything else, the pics are shuted down and the interrupts are disabled
main:
	cli	; The multiboot standard ask for this to be cleared by the multiboot compliant bootloader
		; but I choose to clear it just to be sure
	
	;Shuting down the two pics
	mov eax, 0xFF
	mov edx, 0xA1
	out dx, al

	mov edx, 0x21
	out dx, al

	mov esp, 0x80000
	mov eax, [ebx]
	push ebx
	call init

jump:
	hlt
	jmp jump