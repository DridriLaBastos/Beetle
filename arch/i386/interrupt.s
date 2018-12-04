; This macro creats an interrupt handler that displays the vector of the interrupt currently called to the screen.
; The format of the interrupt is interrupt_<interrupt name>
; Exemple : for the SS interrupt, the symbol created will be interrupt_SS and will display "(12)" on the screen

%macro INTERRUPT 2
global interrupt_%1
    interrupt_%1:
        mov al, '('
        call disp
        mov eax, %2
        call dispn
        mov al, ')'
        call disp
        iretd
%endmacro

SECTION .header
INTERRUPT DE, 0
INTERRUPT DB, 1
INTERRUPT NMI, 2
INTERRUPT BP, 3
INTERRUPT OF, 4
INTERRUPT BR, 5
INTERRUPT UP, 6
INTERRUPT NM, 7
INTERRUPT DF, 8
INTERRUPT CSO, 9
INTERRUPT TS, 10
INTERRUPT NP, 11
INTERRUPT SS, 12
INTERRUPT GP, 13
INTERRUPT PF, 14
INTERRUPT IR, 15
INTERRUPT MF, 16
INTERRUPT AC, 17
INTERRUPT MC, 18
INTERRUPT XM, 19
INTERRUPT VE, 20

;puts the ascii code inside al into the VGA RAM
disp:
    pusha
    mov ah, 0xC
    mov ebx, [pos]
    mov word [0xB8000 + ebx * 2], ax
    inc dword [pos]
    popa
    ret

;displays the number inside eax
global dispn
dispn:
    pusha
    mov ebx, 10
    xor ecx, ecx
    .start:
        xor edx, edx
        div ebx
        push edx
        inc ecx
        cmp eax, 0
        jz .next
        jmp .start
    
    .next:
        pop eax
        add eax, '0'
        call disp
        loop .next
        popa
        ret

SECTION .data
    pos: dd 0
