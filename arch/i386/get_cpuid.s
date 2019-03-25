global get_cpuid

;ecx : cpuid function to call
;edx : addres of the CPUIDResult structur to fill
get_cpuid:
	mov eax, ecx
	cpuid
	mov dword [edx + 4 * 0], eax
	mov dword [edx + 4 * 1], ebx
	mov dword [edx + 4 * 2], ecx
	mov dword [edx + 4 * 3], edx
	ret
