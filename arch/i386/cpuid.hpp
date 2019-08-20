#ifndef CPUID_HPP
#define CPUID_HPP

#include "stdint.h"

namespace ARCH {namespace I386 {namespace CPUID
{
	struct AnswerStruct
	{
		const uint32_t eax;
		const uint32_t ebx;
		const uint32_t ecx;
		const uint32_t edx;
	};
	
	AnswerStruct function (const unsigned int functionNumber);
}}};

#endif //CPUID_HPP‡