#ifndef APIC_HPP
#define APIC_HPP

#include <stdint.h>

namespace ARCH {namespace I386
{
	class APIC
	{
		public:
			enum class TIMER_DIVIDE_VALUE
			{
				D2, D4, D8, D16, D32, D64, D128, D1
			};

		public:
			APIC(void);

		public:
			uint32_t read32bitsRegister (const unsigned int registerNumber);
			void write32bitsRegister (const unsigned int registerNumber, const uint32_t valueToWrite);
			void setTimerDivideValue (const TIMER_DIVIDE_VALUE timerDivideValues);
			void enable (void) const;

		private:
			volatile uint32_t* m_apicRegistersPTR;
	};
}}

#endif