extern init
global main
main:
	xchg bx, bx
	mov esp, 0x80000
	mov eax, [ebx]
	push ebx
	call init
	jmp $