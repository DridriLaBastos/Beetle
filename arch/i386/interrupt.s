global default_int
global gp_int
global ss_int
global np_int
global pf_int
global ac_int
global ud_int


SECTION .text
default_int:
    xchg bx, bx
    mov eax, 0xDEFA0000
    iretd

gp_int:
    xchg bx, bx
    mov eax, 0
    iretd

ss_int:
    xchg bx, bx
    mov eax, 1
    iretd

np_int:
    xchg bx, bx
    mov eax, 2
    iretd

pf_int:
    xchg bx, bx
    mov eax, 3
    iretd

ac_int:
    xchg bx, bx
    mov eax, 4
    iretd

ud_int:
    xchg bx, bx
    mov eax, 4
    iretd