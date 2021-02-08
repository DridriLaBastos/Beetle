extern init
global main

main:
	mov esp, 0x80000
	mov eax, [ebx]
	push ebx
	call init
jump:
	xchg bx, bx
	hlt
	jmp jump