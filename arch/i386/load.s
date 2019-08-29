;bunch of functions that loads a segments
;every function behave the same : the selector to load is passed  by ecx

global load_ds
global load_es
global load_fs
global load_gs
global load_ss

SECTION .text
load_ds:
	mov ax, cx
	mov ds, ax
	ret

load_es:
	mov ax, cx
	mov es, ax
	ret

load_fs:
	mov ax, cx
	mov fs, ax
	ret

load_gs:
	mov ax, cx
	mov gs, ax
	ret

load_ss:
	mov ax, cx
	mov ss, ax
	add esp, edx
	ret