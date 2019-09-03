#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <stdint.h>

//Possible values for the field P of any descriptors
constexpr unsigned int PRESENT		= 1 << 2;
constexpr unsigned int NOT_PRESENT	= 0;

constexpr unsigned int EXEC_32B	= 1 << 2;
constexpr unsigned int EXEC_16B	= 0;

constexpr unsigned int STACK_32B = EXEC_32B;
constexpr unsigned int STACK_16B = EXEC_16B;

constexpr unsigned int LIMIT_4K		= 1 << 3;
constexpr unsigned int LIMIT_BYTES	= 0;

//Possible values for the field S in segment descriptor
//These constants should not be use direcly, there are used in the *_SEGMENT_T enums
constexpr unsigned int SYSTEM(const unsigned int n) { return n; }
constexpr unsigned int CODE_DATA(const unsigned int n) { return n | (1 << 4); }

//Possible values for the field DPL in any descriptors
constexpr unsigned int PRIVILEGE0 = 0;
constexpr unsigned int PRIVILEGE1 = 1;
constexpr unsigned int PRIVILEGE2 = 2;
constexpr unsigned int PRIVILEGE3 = 3;

/**
 * In this namespace any i386 architecture feature will be implemented
 * */
namespace ARCH {namespace I386 {

	struct Register
	{
		uint16_t limit;
		uint32_t base;
	}__attribute__((packed));

	struct Descriptor
	{
		uint32_t low;
		uint32_t high;
	};

	enum CODE_DATA_SEGMENT_T
	{
		D_RO	= CODE_DATA( 0), //Data read only
		D_ROA   = CODE_DATA( 1), //Data read only accessed
		D_RW	= CODE_DATA( 2), //Data read/write
		D_RWA   = CODE_DATA( 3), //Data read/write accessed
		D_ROE   = CODE_DATA( 4), //Data read only expand down
		D_ROEA  = CODE_DATA( 5), //Data read only expand down accessed
		D_RWE   = CODE_DATA( 6), //Data read write expand down
		D_RWEA  = CODE_DATA( 7), //Data read write expand down accessed

		C_EO	= CODE_DATA( 8), //Code execute only
		C_EOA   = CODE_DATA( 9), //Code execute only accessed
		C_ER	= CODE_DATA(10), //Code execute read
		C_ERA   = CODE_DATA(11), //Code execute read accessed
		C_EOC   = CODE_DATA(12), //Code execute only conforming
		C_EOCA  = CODE_DATA(13), //Code execute only confirming accessed
		C_ERC   = CODE_DATA(14), //Code execute read conforming
		C_ERCA  = CODE_DATA(15)  //Code execute read conforming accessed
	};

	enum SYSTEM_SEGMENT_T
	{
		// 0 = reserved
		TSS_A_16 = SYSTEM( 1), //16 bits TSS available
		LDT	  = SYSTEM( 2), //LDT
		TSS_B_16 = SYSTEM( 3), //16 bits TSS busy
		CG_16	= SYSTEM( 4), //16 bits call gate
		TG	   = SYSTEM( 5), //task gate
		IG_16	= SYSTEM( 6), //16 bits interrupt gate
		TG_16	= SYSTEM( 7), //16 bits trap gate
		// 8 = reserved
		TSS_A_32 = SYSTEM( 9), //32 bits TSS available
		// 10 = reserved
		TSS_B_32 = SYSTEM(10), //32 bits TSS busy
		CG_32	= SYSTEM(11), //32 bits call gate
		// 13 = reserved
		IG_32	= SYSTEM(14), //32 bits interrupt gate
		TG_32	= SYSTEM(15)  //32 bits trap gate
	};

	enum class SEGMENT_NAMES
	{
		DS, ES, FS, GS, SS /* There is no CS because cs can't be selected using a move instruction */
	};

	/*inline TDescriptor create_trapgate_descriptor (const uint32_t offset, const uint16_t segment_selector, const int access)
	{
		//Explicite conversion to silent some warnings
		return {(uint16_t)offset, segment_selector, (uint16_t)0x78, (uint16_t)access, (uint16_t)(offset >> 16)};
	}

	inline TaskGateDescriptor create_taskgate_descriptor (const uint16_t tss_segment_selector, const int access)
	{
		TaskGateDescriptor ret;
		ret.tss_segment_selector = tss_segment_selector;
		ret.tss_value = 0b00101;
		ret.access = access;

		return ret;
	}*/

	class Table
	{
		public:
			unsigned int getCount(void) const;
			virtual void makeCurrent(void) const = 0;

		protected:
			Table(const unsigned int base, const unsigned int count);
			void add(const Descriptor descriptor);

		protected:
			Register m_reg;
			unsigned int m_count;
	};


	class GDT: public Table
	{
		public:
			GDT(const unsigned int base, const unsigned int count);

		public:
			void addSegmentDescriptor(const unsigned int base, const unsigned int limit, const unsigned int type, const unsigned int access, const unsigned int other);
			void select (const SEGMENT_NAMES segmentName, const unsigned int segNum, const unsigned int rpl);
			virtual void makeCurrent(void) const final;
		
		private:
			void selectSS(const unsigned int SSDescriptorNum);
			
		private:
			mutable Descriptor m_oldSSDescriptor;
	};

	class IDT: public Table
	{
		public:
			IDT(const unsigned int base, const unsigned int count);

		public:
			void addInterruptGateDescriptor (const unsigned int offset, const unsigned int segment_selector, const unsigned int access, const bool size32 = true);
		
		public:
			virtual void makeCurrent(void) const final;
	};
}}

#endif