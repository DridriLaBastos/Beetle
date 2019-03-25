global switch_idt

SECTION .text
;switch idt : take the address of an idtr structure in ecx
; and then switches the current idt to the one described by this idtr
; this function will be called once at the start of the system
switch_idt:
    lidt [ecx]
    sti
    ret
    