global get_idtr
SECTION .text
;get_idtr return the value stored inside the idtr at the address stored in ecx
get_idtr:
    sidt [ecx]
    ret