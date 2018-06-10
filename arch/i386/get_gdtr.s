global get_gdtr
SECTION .text
;get_gdtr return the value stored inside the gdtr at the address stored in ecx
get_gdtr:
    sgdt [ecx]
    ret