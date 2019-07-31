#include "mem.hpp"

extern "C" 
{
    void __attribute__((fastcall)) switch_idt (const unsigned int idtr_addr);
    void __attribute__((fastcall)) switch_gdt (const unsigned int gdtr_addr);
}

/* *** GENERAL TABLE CLASS *** */
ARCH::I386::Table::Table(const unsigned int base, const unsigned int count): m_count(0)
{
	m_reg.base = base;
	m_reg.limit = 8*count - 1;
}

void ARCH::I386::Table::add (const ARCH::I386::Descriptor descriptor)
{
	uint32_t* descriptorPtr = (uint32_t*)m_reg.base;
	descriptorPtr[2*m_count] = descriptor.low;
	descriptorPtr[2*m_count+1] = descriptor.high;
	++m_count;
}

unsigned int ARCH::I386::Table::getCount(void) const
{ return m_count; }

/* *** GDT *** */
ARCH::I386::GDT::GDT(const unsigned int base, const unsigned int count): Table(base, count)
{ add({0,0}); }

void ARCH::I386::GDT::addSegmentDescriptor(const unsigned int base, const unsigned int limit, const unsigned int type, const unsigned int access, const unsigned int other)
{
	const unsigned int segmentDescriptorHighLow		= ((((access & 0b111) << 4) | type) << 8) | ((base & 0xFF0000) >> 16);
	const unsigned int segmentDescriptorHighHigh	= ((base & 0xFF000000) >> 16) | (((other & 0xF) << 4) | ((limit & 0xF0000) >> 16));

	const unsigned int segmentDescriptorLow 	= ((base && 0xFFFF) << 16) | (limit & 0xFFFF);
	const unsigned int segmentDescriptorHigh	= (segmentDescriptorHighHigh << 16) | segmentDescriptorHighLow;
	
	add({segmentDescriptorLow, segmentDescriptorHigh});
}

void ARCH::I386::GDT::makeCurrent(void) const
{ switch_gdt((unsigned int)&m_reg); }

/* *** IDT *** */
ARCH::I386::IDT::IDT(const unsigned int base, const unsigned int count): Table(base, count){}

void ARCH::I386::IDT::addInterruptGateDescriptor (const unsigned int offset, const unsigned int segment_selector, const unsigned int access, const bool size32)
{
	const unsigned int descriptorHighLow = ((access & 0b111) << 16) | ((size32 ? 1 : 0) << 11) | (0b110 << 10);
	const unsigned int descriptorLow	= ((offset & 0xFFFF) << 16) | segment_selector;
	const unsigned int descriptorHigh	= (offset & 0xFFFF0000) | descriptorHighLow;

	add({descriptorLow, descriptorHigh});
}

void ARCH::I386::IDT::makeCurrent(void) const
{ switch_idt((unsigned int)&m_reg); }