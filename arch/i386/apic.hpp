#ifndef ACPI_HPP
#define ACPI_HPP

namespace ARCH::I386::APIC::LVT
{
	enum D_MODE
	{
		FIXED = 0b000,
		SMI   = 0b010,
		NMI   = 0b100,
		INIT  = 0b101,
		EINT  = 0b111
	};

	enum D_STAT
	{
		IDLE    = 0,
		PENDING = 1
	};

	enum T_MODE
	{
		EDGE  = 0,
		LEVEL = 1
	};

	enum MASK
	{
		NOT_MASKED = 0,
		MASKED     = 1
	};

	enum TI_MODE
	{
		ONE_SHOT = 0b00,
		PERIODIC = 0b01,
		TSC_DEADLINE = 0b10
	};

	/**
	 * \struct ARCH::I386::APIC::LVT::LINTRegister apic.hpp
	 * Defines the structure of the LINT0 and LINT1 register in the LVT of a local APIC
	 * 
	 * - vector : the interrupt vector to be transferred to the CPU
	 * - d_mod  : the Delivery Mode   (see the enum ARCH::I386::APIC::LVT::D_MODE)
	 * - d_stat : the Delivery Status (see the enum ARCH::I386::APIC::LVT::D_STAT)
	 * - iipp   : the Interrupt Input Pin Polarity
	 * - remote_irr : the Remote IRR
	 * - t_mode : the Trigger MODE (see the enum ARCH::I386::APIC::LVT::T_MODE)
	 * - mask   : the MASK (ARCH::I386::APIC::LVT::MASK)
	 */
	union LINTRegister
	{
		uint32_t int_value;
		uint32_t vector:8, d_mode:3, :1, d_stat:1, iipp:1, remote_irr:1, t_mode:1, mask:1;
	};

	/**
	 * \struct ARCH::I386::APIC::LVT::Register apic.hpp
	 * Defines the structure of a generic register in the LVT of a local APIC
	 * 
	 * - vector : the interrupt vector to be transferred to the CPU
	 * - d_mode : the Delivery Mode   (see the enum ARCH::I386::APIC::LVT::D_MODE)
	 * - d_stat : the Delivery Status (see the enum ARCH::I386::APIC::LVT::D_STAT)
	 * - mask   : the MASK (ARCH::I386::APIC::LVT::MASK)
	 */
	union Register
	{
		uint32_t int_value;
		uint32_t vector:8, d_mode:3, :1, d_stat:1, :3, mask:1;
	};

	/**
	 * \struct ARCH::I386::APIC::LVT::TIMERRegister apic.hpp
	 * Defines the structure of the Timer register in the LVT of a local APIC
	 * 
	 * - vector : the interrupt vector to be transferred to the CPU
	 * - d_stat : the Delivery Status (see the enum ARCH::I386::APIC::LVT::D_STAT)
	 * - mask   : the MASK (ARCH::I386::APIC::LVT::MASK)
	 * - ti_mode : the Timer MODE (see the enum ARCH::I386::APIC::LVT::TI_MODE)
	 */
	union TIMERRegister
	{
		uint32_t int_value;
		uint32_t vector:8, :4, d_stat:1, :3, mask:1, ti_mode:2;
	};

	inline LINTRegister create_lint_register (const unsigned int vec, const D_MODE d_mode, const D_STAT d_stat, const unsigned int iipp, const unsigned int remote_irr, const T_MODE t_mode, const MASK mask)
	{ 
		LINTRegister result;
		result.vector = vec; result.d_mode = d_mode; result.d_stat = d_stat; result.iipp = iipp; result.remote_irr = remote_irr; result.t_mode = t_mode; result.mask = mask;
		return result; 
	}

	inline Register create_apic_register (const unsigned int vec, const D_MODE d_mode, D_STAT d_stat, const MASK mask)
	{ 
		Register result;
		result.vector = vec; result.d_mode = d_mode; result.d_stat = d_stat; result.mask = mask;
		return result;
	}

	inline TIMERRegister create_timer_register(const unsigned int vec, const D_STAT d_stat, const MASK mask, const TI_MODE ti_mode)
	{
		TIMERRegister result;
		result.vector = vec; result.d_stat = d_stat; result.mask = mask; result.ti_mode = ti_mode; 
		return result;
	}
}

#endif