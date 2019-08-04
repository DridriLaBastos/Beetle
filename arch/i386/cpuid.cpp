#include "cpuid.hpp"

extern "C" void __attribute__((fastcall)) get_cpuid (const unsigned int functionNumber, const unsigned int CPUIDAnswerStructAddress);

ARCH::I386::CPUID::AnswerStruct ARCH::I386::CPUID::function(const unsigned int functionNum)
{
	AnswerStruct answerStruct = {};
	get_cpuid(functionNum, (unsigned int)&answerStruct);
	return answerStruct;
}