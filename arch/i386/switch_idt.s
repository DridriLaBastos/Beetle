global switch_idt

SECTION .text
;switch idt : take the address of an idtr structure in ecx
; and then switches the current idt to the one described by this idtr
; this function will be called once at the start of the system
switch_idt:
    lidt [ecx]
    ;Disabling the two PICs, we want to use APIC instead
    mov al, 0xFF
    out 0xA1, al
    out 0x21, al
    sti
    ret