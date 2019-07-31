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

;Loading ss is a littlebit trickier than loading other segment, we have to recover the informations stored in the old stack and copy theme in the new stack before
;performing the switch
load_ss:
    mov ax, cx
    mov ss, ax
    ret