global switch_gdt

;Switch to a new GDT defined by the datastructure to put on GDTR pointed to by ecx
SECTION .text
switch_gdt:
    lgdt [ecx]
    jmp 0x08:.next;<-- 0x08 will be loaded with a flat code segment with a privilege level to 0
    .next:
    ret