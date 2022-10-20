#ifndef __I386_HPP__
#define __I386_HPP__

#include "../../../libc/stdint.h"

namespace ARCH::I386 {

#pragma region "Constant Definitions"
	namespace DESCRIPTOR {
		constexpr unsigned int PRIVILEGE0 = 0;
		constexpr unsigned int PRIVILEGE1 = 1;
		constexpr unsigned int PRIVILEGE2 = 2;
		constexpr unsigned int PRIVILEGE3 = 3;
		
		constexpr unsigned int GRANULARITY_BYTES = 0;
		constexpr unsigned int GRANULARITY_4K = 1;

		constexpr unsigned int SIZE_16b = 0;
		constexpr unsigned int SIZE_32b = 1;

		/* Types include the S flags */
		enum TYPE{
			/* SYSTEM TYPE */
			//Reserved
			SYSTEM_16b_TSSA=1,//16 birs TSS available
			SYSTEM_LDT,
			SYSTEM_16b_TSSB,
			SYSTEM_16b_CG,
			SYSTEM_TG,
			SYSTEM_16b_IG,
			SYSTEM_16b_TG,
			//Reserved
			SYSTEM_32b_TSSA=0b1001,
			//Reserved
			SYSTEM_32b_TSSB=0b1011,
			SYSTEM_32b_TSSCG,
			//Reserved
			SYSTEM_32b_IG=0b1110,
			SYSTEM_32b_TG,

			/* DATA TYPE */
			DATA_RO = 0b10000,//Read-only
			DATA_ROA,//Read-only accessed
			DATA_RW,//Read/write
			DATA_RWA,//Read/write accessed

			DATA_ROD,//Read-only expand-down
			DATA_ROAD,//Read-only expand-down accessed
			DATA_RWD,//Read-write expand-down accessed
			DATA_RWAD,//Read-write expand-down accessed
			
			/* EXECUTE TYPE */
			EXECUTE_O,//Execute-only
			EXECUTE_OA,//Execute-only accessed
			EXECUTE_R,//Execute/write
			EXECUTE_RA,//Execute/write accessed

			EXECUTE_OC,//Execute-only conforming
			EXECUTE_OAC,//Execute-only accessed conforming
			EXECUTE_RC,//Execute/write conforming
			EXECUTE_RAC,//Execute/write accessed conforming
		};
	}
#pragma endregion

#pragma region "Descriptor Operations"
	using descriptor_t = uint64_t;

	struct SystemTableRegisterDescription {
		uint16_t limit;
		uint32_t linearBaseAddress;
	} __attribute__((packed)) ;

	constexpr descriptor_t CreateSegmentDescriptor(const uint32_t base, const uint32_t limit, ARCH::I386::DESCRIPTOR::TYPE type, const uint8_t DPL, const unsigned int G, const unsigned int DB)
	{
		const descriptor_t d1 = (uint16_t)limit;
		const descriptor_t d2 = (uint16_t)base;
		const descriptor_t d3 = ((DPL | 0b1000) << 12) | (type << 8) | ((base >> 16) & 0xFF);

		//avl and l put 0 because not used (l only meaningfull in 32e mode and avl not used by the OS)
		const unsigned int other = (G << 3) | (DB << 2);
		const descriptor_t d4 = ((base >> 16) & 0xFF00) | (other << 4) | ((limit >> 16) & 0xF) ;
		return (d4 << 48) | (d3 << 32) | (d2 << 16) | d1;
	}

	//void pushDescriptor(tinfo& i, const descriptor_t descriptor);
#pragma endregion

#pragma region "Port IO Operations"
	static inline void outb (const uint8_t value, const uint16_t addr)
		{ asm ("outb %0, %1":: "a" (value), "dx" (addr)); }
		static inline void outw (const uint16_t value, const uint16_t addr)
		{ asm ("outw %0, %1":: "a" (value), "dx" (addr)); }
		static inline void outd (const uint32_t value, const uint16_t addr)
		{ asm ("outd %0, %1":: "a" (value), "dx" (addr)); }

		static inline uint8_t inb (const uint16_t addr)
		{
			uint8_t result = 0;
			asm ("inb %1, %0" : "=a" (result) : "dx" (addr));
			return result;
		}

		static inline uint16_t inw (const uint16_t addr)
		{
			uint16_t result = 0;
			asm ("inw %1, %0" : "=a" (result) : "dx" (addr));
			return result;
		}

		static inline uint32_t ind (const uint16_t addr)
		{
			uint32_t result = 0;
			asm ("ind %1, %0" : "=a" (result) : "dx" (addr));
			return result;
		}
#pragma endregion

#pragma region "Arch interruptions"
	__attribute__((interrupt)) void interruptDE  (const void* ptr);
	__attribute__((interrupt)) void interruptDB  (const void* ptr);
	__attribute__((interrupt)) void interruptNMI (const void* ptr);
	__attribute__((interrupt)) void interruptBP  (const void* ptr);
	__attribute__((interrupt)) void interruptOF  (const void* ptr);
	__attribute__((interrupt)) void interruptBR  (const void* ptr);
	__attribute__((interrupt)) void interruptUD  (const void* ptr);
	__attribute__((interrupt)) void interruptNM  (const void* ptr);
	__attribute__((interrupt)) void interruptDF  (const void* ptr);
	__attribute__((interrupt)) void interruptCS  (const void* ptr);
	__attribute__((interrupt)) void interruptTS  (const void* ptr);
	__attribute__((interrupt)) void interruptNP  (const void* ptr);
	__attribute__((interrupt)) void interruptSS  (const void* ptr);
	__attribute__((interrupt)) void interruptGP  (const void* ptr);
	__attribute__((interrupt)) void interruptPF  (const void* ptr);
	__attribute__((interrupt)) void interruptMF  (const void* ptr);
	__attribute__((interrupt)) void interruptAC  (const void* ptr);
	__attribute__((interrupt)) void interruptMC  (const void* ptr);
	__attribute__((interrupt)) void interruptXM  (const void* ptr);
	__attribute__((interrupt)) void interruptVE  (const void* ptr);
	 
	__attribute__((interrupt)) void irq0 (const void* ptr);
	__attribute__((interrupt)) void irq1 (const void* ptr);
	__attribute__((interrupt)) void irq2 (const void* ptr);
	__attribute__((interrupt)) void irq3 (const void* ptr);
	__attribute__((interrupt)) void irq4 (const void* ptr);
	__attribute__((interrupt)) void irq5 (const void* ptr);
	__attribute__((interrupt)) void irq6 (const void* ptr);
	__attribute__((interrupt)) void irq7 (const void* ptr);

	__attribute__((interrupt)) void irq8 (const void* ptr);
	__attribute__((interrupt)) void irq9 (const void* ptr);
	//__attribute__((interrupt)) void irq10 (const void* ptr); reserved
	//__attribute__((interrupt)) void irq11 (const void* ptr); reserved
	//__attribute__((interrupt)) void irq12 (const void* ptr); reserved
	__attribute__((interrupt)) void irq13 (const void* ptr);
	__attribute__((interrupt)) void irq14 (const void* ptr);
	//__attribute__((interrupt)) void irq15 (const void* ptr); reserved
#pragma endregion
}

#endif
