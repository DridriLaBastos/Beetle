#include "apic.hpp"

constexpr unsigned int LVT_BASE_POS = 0x32;
constexpr unsigned int CMCI_REG_LVT_POS = 0x2F;

namespace ARCH::I386::LOCAL_APIC
{
	uint32_t read_entry(const unsigned int n)
	{
		uint32_t* apic_registers = (uint32_t*)(0xFEE00000);
		return apic_registers[n * 4];
	}

	uint32_t read_version (void) 
	{
		return read_entry(3);
	}

	void write_entry (const unsigned int n, const uint32_t v)
	{
		uint32_t* apic_registers = (uint32_t*)(0xFEE00000);
		apic_registers[n * 4] = v;
	}

	void software_enable ()
	{
		uint32_t spurious_vector = read_entry(0xF);
		spurious_vector |= 1 << 11;
		write_entry(0xF,spurious_vector);
	}

	void software_disable()
	{
		uint32_t spurious_vector = read_entry(0xF);
		spurious_vector &= ~(1 << 11);
		write_entry(0xF,spurious_vector);
	}

	void LVT::write_lvt_reg(const uint32_t reg_value, const LVT::REGISTER reg)
	{ write_entry(LVT_BASE_POS + (unsigned)reg_value,reg_value); }

	void LVT::write_cmci_reg(const uint32_t reg_value)
	{ write_entry(CMCI_REG_LVT_POS,reg_value); }
}