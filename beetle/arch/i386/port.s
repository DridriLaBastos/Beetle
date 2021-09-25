%macro FUNC 1
	global %1
	%1:
%endmacro

FUNC outb
	mov eax, ecx
	out dx, al
	ret

FUNC outw
	mov eax, ecx
	out dx, ax
	ret

FUNC outd
	mov eax, ecx
	out dx, eax
	ret

FUNC inb
	in al, dx
	ret

FUNC inw
	in ax, dx
	ret

FUNC ind
	in eax, dx
	ret