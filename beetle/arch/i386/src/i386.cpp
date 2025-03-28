#include <stdint.h>

#include <beetle/arch.hpp>

static constexpr unsigned int PRIVILEGE0 = 0;
static constexpr unsigned int PRIVILEGE1 = 1;
static constexpr unsigned int PRIVILEGE2 = 2;
static constexpr unsigned int PRIVILEGE3 = 3;

static constexpr unsigned int GRANULARITY_BYTES = 0;
static constexpr unsigned int GRANULARITY_4K = 1;

static constexpr unsigned int SIZE_16b = 0;
static constexpr unsigned int SIZE_32b = 1;

static constexpr unsigned int N_GDT_SELECTOR = 16;
static constexpr unsigned int N_IDT_SELECTOR = 256;

/* Types include the S flags */
enum class DESCRIPTOR_TYPE{
	/* SYSTEM TYPE */
	//Reserved
	SYSTEM_16b_TSSA=1,//16 bit TSS available
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

using descriptor_t = uint64_t;

struct SystemTableRegister {
	uint16_t limit;
	uint32_t linearBaseAddress;
} __attribute__((packed)) ;

static constexpr descriptor_t CreateSegmentDescriptor(const uint32_t base, const unsigned int limit, DESCRIPTOR_TYPE type, const uint8_t DPL, const unsigned int G, const unsigned int size)
{
	const descriptor_t d1 = static_cast<uint16_t>(limit);
	const descriptor_t d2 = static_cast<uint16_t>(base);
	const descriptor_t d3 = ((DPL | 0b1000) << 12) | (static_cast<int>(type) << 8) | ((base >> 16) & 0xFF);

	//avl and l put 0 because not used (l only meaningful in 32e mode and avl not used by the OS)
	const unsigned int other = (G << 3) | (size << 2);
	const descriptor_t d4 = ((base >> 16) & 0xFF00) | (other << 4) | ((limit >> 16) & 0xF) ;
	return (d4 << 48) | (d3 << 32) | (d2 << 16) | d1;
}

extern "C" {
	descriptor_t gdt [N_GDT_SELECTOR] = {
		// From intel doc first entry in the GDT must be 0
		0,
		//kernel code
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::EXECUTE_R,PRIVILEGE0,GRANULARITY_4K,SIZE_32b),
		//kernel data
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::DATA_RW,PRIVILEGE0,GRANULARITY_4K,SIZE_32b),
		//kernel stack need to be created depending on the available memory
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::DATA_RW,PRIVILEGE0,GRANULARITY_4K,SIZE_32b),

		//user code
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::EXECUTE_R,PRIVILEGE3,GRANULARITY_4K,SIZE_32b),
		//user data
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::DATA_RW,PRIVILEGE3,GRANULARITY_4K,SIZE_32b),
		//user stack needs to be created depending on the available memory
		CreateSegmentDescriptor(0,0xFFFFF,DESCRIPTOR_TYPE::DATA_RW,PRIVILEGE3,GRANULARITY_4K,SIZE_32b),
		0,
	};

	descriptor_t idt [N_IDT_SELECTOR];

	SystemTableRegister gdtr = { .limit = sizeof(gdt) - 1, .linearBaseAddress = (uint32_t)(uintptr_t)gdt };
	SystemTableRegister idtr = { .limit = sizeof(idt) - 1, .linearBaseAddress = (uint32_t)(uintptr_t)idt };
}

void ARCH::Init(void* firstAvailableMemory)
{

}

void ARCH::EndlessLoop(void)
{
	while (true)
	{
		__asm__ ("cli");
		__asm__ ("hlt");
	}
}
