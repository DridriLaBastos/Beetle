global get_cpuid

;ecx : cpuid function to call
;edx : addres of the CPUIDResult structur to fill
get_cpuid:
	xchg bx, bx
	mov eax, ecx
	mov edi, edx
	cpuid
	mov dword [edi + 4 * 0], eax
	mov dword [edi + 4 * 1], ebx
	mov dword [edi + 4 * 2], ecx
	mov dword [edi + 4 * 3], edx
	ret
