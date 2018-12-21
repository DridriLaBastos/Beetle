#ifndef CPUID_HPP
#define CPUID_HPP

// A bit ugly but needed until I find a better design (or not)
namespace ARCH::I386
{
	struct CPUIDResult
	{
		unsigned int eax;
		unsigned int ebx;
		unsigned int ecx;
		unsigned int edx;
	} __attribute__((packed));
}

extern "C"
{
	__attribute__((fastcall)) void get_cpuid (const unsigned int cpuid_func, const ARCH::I386::CPUIDResult* cpuid_result_addr);
}

namespace ARCH::I386
{
	struct CPUID
	{
		enum class FUNCTIONS
		{
			ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, HEIGHT, NINE,
			TEN
		};

		CPUID (const FUNCTIONS f): result({0, 0, 0, 0})
		{ get_cpuid(static_cast<unsigned int>(f), &result); }

		CPUIDResult result;
	};

	void cpuid_0 (void);
}

#endif