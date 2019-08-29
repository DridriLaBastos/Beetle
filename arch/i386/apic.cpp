#include "apic.hpp"

ARCH::I386::APIC::APIC(): m_apicRegistersPTR((volatile uint32_t*)0xFEE00000) {}

uint32_t ARCH::I386::APIC::read32bitsRegister(const unsigned int registerNumber)
{ return m_apicRegistersPTR[registerNumber << 2]; }

void ARCH::I386::APIC::write32bitsRegister(const unsigned int registerNumber, const uint32_t valueToWrite)
{ m_apicRegistersPTR[registerNumber << 2] = valueToWrite; }

void ARCH::I386::APIC::enable() const
{
}

void ARCH::I386::APIC::setTimerDivideValue(const ARCH::I386::APIC::TIMER_DIVIDE_VALUE timerDivideValue)
{
	const unsigned int timerDivideValueIntValue = static_cast<unsigned int>(timerDivideValue);
	const unsigned int timerDivideValueToWrite = ((timerDivideValueIntValue & 0b100) << 1) | (timerDivideValueIntValue & 0b11);
	asm("xchg %bx, %bx");
	write32bitsRegister(62, timerDivideValueToWrite);
}