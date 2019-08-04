extern init
global main
main:
	mov esp, 0x80000
	
	call init
	jmp $