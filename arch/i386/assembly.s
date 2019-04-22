;This file regroups all assembly functions needed ofr the i386 platforms
global get_cpuid, get_gdtr, get_idtr, switch_gdt, switch_idt

SECTION .text
;ecx : cpuid function to call
;edx : addres of the CPUIDResult structur to fill
get_cpuid:
	mov eax, ecx
    mov edi, edx
    xchg bx, bx
	cpuid
	mov dword [edi + 4 * 0], eax
	mov dword [edi + 4 * 1], ebx
	mov dword [edi + 4 * 2], ecx
	mov dword [edi + 4 * 3], edx
	ret

;get_gdtr return the value stored inside the gdtr at the address stored in ecx
get_gdtr:
    sgdt [ecx]
    ret

;get_idtr return the value stored inside the idtr at the address stored in ecx
get_idtr:
    sidt [ecx]
    ret

;Switch to a new GDT defined by the datastructure to put on GDTR pointed to by ecx
switch_gdt:
    lgdt [ecx]
    jmp 0x08:.next;<-- 0x08 will be loaded with a flat code segment with a privilege level to 0
    .next:
    ret

;switch idt : take the address of an idtr structure in ecx
; and then switches the current idt to the one described by this idtr
; this function will be called once at the start of the system
switch_idt:
    lidt [ecx]
    sti
    ret