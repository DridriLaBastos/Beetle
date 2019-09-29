[BITS 32]

%macro FUNCTION 1
global %1
%1:
%endmacro

SECTION .text
;ecx : cpuid function to call
;edx : addres of the CPUIDResult structur to fill
FUNCTION get_cpuid
	mov eax, ecx
	mov edi, edx
	cpuid
	mov dword [edi + 4 * 0], eax
	mov dword [edi + 4 * 1], ebx
	mov dword [edi + 4 * 2], ecx
	mov dword [edi + 4 * 3], edx
	ret

;Switch to a new GDT defined by the datastructure to put on GDTR pointed to by ecx
FUNCTION switch_gdt
	lgdt [ecx]
	jmp 0x08:.next;<-- 0x08 will be loaded with a flat code segment with a privilege level to 0
	.next:
	ret

;switch idt : take the address of an idtr structure in ecx
; and then switches the current idt to the one described by this idtr
; this function will be called once at the start of the system
FUNCTION switch_idt
	lidt [ecx]
	sti
	ret

FUNCTION getCurrentSSDescriptorLow
	push ebx
	sgdt [gdtrStruct]
	mov ebx, [gdtrStruct + 2]
	xor eax, eax
	mov ax, ss
	mov eax, [ebx + eax]
	pop ebx
	ret

FUNCTION getCurrentSSDescriptorHigh
	push ebx
	sgdt [gdtrStruct]
	mov ebx, [gdtrStruct + 2]
	xor eax, eax
	mov ax, ss
	mov eax, [ebx + eax + 4]
	pop ebx
	ret

;bunch of functions to write value to an I/O port. Those functions use the fastcall ABI:
;	ecx --> data to write
;	edx --> port number
FUNCTION outb
	mov eax, ecx
	out dx, al
	ret

FUNCTION outw
	mov eax, ecx
	out dx, ax
	ret

FUNCTION outd
	mov eax, ecx
	out dx, eax
	ret

;TODO: find if there is an ABI that permit with gcc to directly pass the first parameter into edx
;bunch of functions to read data to an I/O port. Those functions uses the thiscall ABI:
;	ecx --> port number to read
FUNCTION inb
	mov edx, ecx
	in al, dx
	and eax, 0xFF
	ret

FUNCTION inw
	mov edx, ecx
	in ax, dx
	and eax, 0xFFFF
	ret

FUNCTION ind
	mov edx, ecx
	in eax, dx
	ret

section .data
	gdtrStruct: db 0, 0, 0