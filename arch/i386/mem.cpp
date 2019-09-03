#include "mem.hpp"

extern "C" 
{
	void __attribute__((fastcall)) switch_idt (const unsigned int idtr_addr);
	void __attribute__((fastcall)) switch_gdt (const unsigned int gdtr_addr);
	void __attribute__((fastcall)) load_ss (const unsigned int descriptorValue, const int espRemapValue);
	void __attribute__((fastcall)) load_ds (const unsigned int descriptorValue);
	void __attribute__((fastcall)) load_es (const unsigned int descriptorValue);
	void __attribute__((fastcall)) load_fs (const unsigned int descriptorValue);
	void __attribute__((fastcall)) load_gs (const unsigned int descriptorValue);
	unsigned int getCurrentSSDescriptorLow (void);
	unsigned int getCurrentSSDescriptorHigh(void);
}

static unsigned int extractBaseAddressFromSegmentDescriptor (const ARCH::I386::Descriptor& descriptor)
{
	const unsigned int addressLow = descriptor.low >> 16;
	const unsigned int addressHigh = ((descriptor.high & 0xFF000000) >> 16) | (descriptor.high & 0xFF);

	return (addressHigh << 16) | addressLow;
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
	const unsigned int segmentDescriptorHighLowBase = (base & 0xFF0000) >> 16;
	const unsigned int segmentDescriptorHighLow		= ((access & 0b111) << 13) | ((type & 0b11111) << 8) | segmentDescriptorHighLowBase;

	const unsigned int segmentDescriptorHighHighBase = (base & 0xFF000000) >> 16;
	const unsigned int segmentDescriptorHighHigh	= segmentDescriptorHighHighBase | ((other & 0xF) << 4) | ((limit & 0xF0000) >> 16);

	const unsigned int segmentDescriptorLow 	= ((base & 0xFFFF) << 16) | (limit & 0xFFFF);
	const unsigned int segmentDescriptorHigh	= (segmentDescriptorHighHigh << 16) | segmentDescriptorHighLow;
	
	add({segmentDescriptorLow, segmentDescriptorHigh});
}

void ARCH::I386::GDT::select (const SEGMENT_NAMES segmentName, const unsigned int segNum, const unsigned int rpl)
{
	const unsigned int SegmentSelectorValue = (segNum << 3) | rpl;
	switch (segmentName)
	{
		case SEGMENT_NAMES::DS:
			load_ds(SegmentSelectorValue);
			break;
		
		case SEGMENT_NAMES::ES:
			load_es(SegmentSelectorValue);
			break;
		
		case SEGMENT_NAMES::FS:
			load_fs(SegmentSelectorValue);
			break;
		
		case SEGMENT_NAMES::GS:
			load_gs(SegmentSelectorValue);
			break;

		//TODO: why remaping esp doesn't work
		case SEGMENT_NAMES::SS:
			selectSS(SegmentSelectorValue);
			break;
	default:
		break;
	}
}

void ARCH::I386::GDT::selectSS(const unsigned int SSDescriptorNum)
{
	const unsigned int SSDescriptorGDTOffset = SSDescriptorNum >> 3;
	const unsigned int currSSBase = extractBaseAddressFromSegmentDescriptor({m_oldSSDescriptor.low, m_oldSSDescriptor.high});

	const unsigned int newSSDescriptorLow = ((uint32_t*)m_reg.base)[SSDescriptorGDTOffset];
	const unsigned int newSSDescriptorHigh = ((uint32_t*)m_reg.base)[SSDescriptorGDTOffset + 1];
	const unsigned int newSSBase = extractBaseAddressFromSegmentDescriptor({newSSDescriptorLow , newSSDescriptorHigh});

	const int SSBaseDiff = currSSBase - newSSBase;

	load_ss(SSDescriptorNum, SSBaseDiff);
}

void ARCH::I386::GDT::makeCurrent(void) const
{
	m_oldSSDescriptor.low = getCurrentSSDescriptorLow();
	m_oldSSDescriptor.high = getCurrentSSDescriptorHigh();
	switch_gdt((unsigned int)&m_reg);
}

/* *** IDT *** */
ARCH::I386::IDT::IDT(const unsigned int base, const unsigned int count): Table(base, count){}

void ARCH::I386::IDT::addInterruptGateDescriptor (const unsigned int offset, const unsigned int segment_selector, const unsigned int access, const bool size32)
{
	const unsigned int descriptorHighLow = ((access & 0b111) << 13) | ((size32 ? 1 : 0) << 11) | (0b11 << 9);

	const unsigned int descriptorLow	= (segment_selector << 16) | (offset & 0xFFFF);
	const unsigned int descriptorHigh	= (offset & 0xFFFF0000) | descriptorHighLow;

	add({descriptorLow, descriptorHigh});
}

void ARCH::I386::IDT::makeCurrent(void) const
{ switch_idt((unsigned int)&m_reg); }