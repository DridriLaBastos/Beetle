#include <stdint.h>

#include <ksys/ksys.h>
#include <beetle/arch.hpp>

#include <kstring.h>

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
using segment_selector_t = uint16_t;

struct SystemTableRegister {
	uint16_t limit;
	uint32_t linearBaseAddress;
} __attribute__((packed));

union USegmentDescriptor {
	descriptor_t uival;

	// The s flags is included in the type
	struct {
		uint64_t limit_15_0:16, base_23_0:24, type:5,dpl:2,p:1,limit_19_16:4, avl:1,l:1,db:1,g:1,base_31_24:8;
	} fields;
};

union ULimitDescriptorField {
	uint32_t uival;

	struct {
		uint32_t limit_15_0:16, limit_19_16:4, unused:12;
	} fields ;
};

union UBaseDescriptorField {
	uint32_t uival;

	struct {
		uint32_t base_23_0: 24, base_31_24:8;
	} fields;
};

struct TSS{
	uint16_t tslink,_tslink_unused;
	uint32_t esp0;
	uint16_t ss0, _ss0_unused;
	uint32_t esp1;
	uint16_t ss1, _ss1_ununsed;
	uint32_t esp2;
	uint16_t ss2, _ss2_unused;
	uint32_t cr3,eip,eflags,eax,ecx,edx,ebx,esp,ebp,esi,edi;
	uint16_t es, _es_unused;
	uint16_t cs, _cs_unused;
	uint16_t ss, _ss_unused;
	uint16_t ds, _ds_unused;
	uint16_t fs, _fs_unused;
	uint16_t gs, _gs_unused;
	uint16_t ldt, _ldt_unused;
	uint16_t t:1,_iomap_unused:15,iomap;
} __attribute__((packed));

static constexpr USegmentDescriptor CreateSegmentDescriptor(const uint32_t base, const unsigned int limit, DESCRIPTOR_TYPE type, const uint8_t DPL, const unsigned int G, const unsigned int size)
{
	UBaseDescriptorField baseFields { .uival = base };
	ULimitDescriptorField limitFields { .uival = limit };
	USegmentDescriptor descriptor { .uival = 0 };

	descriptor.fields.base_23_0 = baseFields.fields.base_23_0;
	descriptor.fields.base_31_24 = baseFields.fields.base_31_24;

	descriptor.fields.limit_15_0 = limitFields.fields.limit_15_0;
	descriptor.fields.limit_19_16 = limitFields.fields.limit_19_16;

	descriptor.fields.limit_15_0 = limitFields.fields.limit_15_0;
	descriptor.fields.limit_19_16 = limitFields.fields.limit_19_16;

	descriptor.fields.type = (unsigned int)type & 0b11111;
	descriptor.fields.dpl = DPL & 0b11;
	descriptor.fields.p = 1;
	descriptor.fields.avl = 0;
	descriptor.fields.l = 0;
	descriptor.fields.db = size & 0b1;
	descriptor.fields.g = G & 0b1;

	return descriptor;
}

static constexpr USegmentDescriptor CreateTSSDescriptor(const uint32_t base)
{
	// From intel doc : 'when G flag is 0, the limit must 0x67 : one less than the minimum size of a TSS'
	return CreateSegmentDescriptor(base,0x67,DESCRIPTOR_TYPE::SYSTEM_32b_TSSA,PRIVILEGE0,0,SIZE_32b);
}

union SegmentSelector {
	segment_selector_t intvalue;

	struct {
		segment_selector_t rpl:2,ti:1,index:13;
	};
};

static constexpr segment_selector_t CreateSegmentSelector(const unsigned int index, const unsigned int RPL, const bool ldt = false)
{
	//sanity check
	static_assert(sizeof(SegmentSelector) == sizeof(segment_selector_t), "SegmentSelector union and segment_selector_t defined type sizes mismatched : the size for both must be 2 bytes (16bits)");
	SegmentSelector ss { .rpl = RPL, .ti = ldt, .index = index };
	return ss.intvalue;
}

extern "C" {
	USegmentDescriptor gdt [N_GDT_SELECTOR];

	descriptor_t idt [N_IDT_SELECTOR];

	SystemTableRegister gdtr = { .limit = sizeof(gdt) - 1, .linearBaseAddress = (uint32_t)(uintptr_t)gdt };
	SystemTableRegister idtr = { .limit = sizeof(idt) - 1, .linearBaseAddress = (uint32_t)(uintptr_t)idt };
}

#define COM1_BASE 0x3F8

static void InitSerial()
{
	koutb(0x00,COM1_BASE + 1);    // Disable all interrupts
   	koutb(0x80,COM1_BASE + 3);    // Enable DLAB (set baud rate divisor)
   	koutb(0x01,COM1_BASE + 0);    // Set divisor to 1 (lo byte) 115200 baud
   	koutb(0x00,COM1_BASE + 1);    //                  (hi byte)
   	koutb(0x03,COM1_BASE + 3);    // 8 bits, no parity, one stop bit
   	koutb(0xC7,COM1_BASE + 2);    // Enable FIFO, clear them, with 14-byte threshold
   	koutb(0x0B,COM1_BASE + 4);    // IRQs enabled, RTS/DSR set
   	koutb(0x1E,COM1_BASE + 4);    // Set in loopback mode, test the serial chip
   	koutb(0xAE,COM1_BASE + 0);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

   // Check if serial is faulty (i.e: not same byte as sent)
	// if(inb(PORT + 0) != 0xAE) {
    // 	return;
	// }

   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   koutb(0x0F,COM1_BASE + 4);
}

void ARCH::Init(void* firstAvailableMemory)
{
	//Sanity checks
	static_assert(sizeof(void*) == sizeof(uint32_t), "Not compiling for i386 architecture : void* is greater than 32bits");
	static_assert(sizeof(uintptr_t) == sizeof(uint32_t), "Not compiling for i386 architecture : uintptr_t is greater than 32bits");

	InitSerial();
}

void ARCH::EndlessLoop(void)
{
	while (true)
	{
		__asm__ ("cli");
		__asm__ ("hlt");
	}
}

void ARCH::MoveToUserLand(void *execFileBaseAddress, void *linearAddress)
{
	gdt[4] = CreateSegmentDescriptor((uintptr_t)execFileBaseAddress, 0xFFFF, DESCRIPTOR_TYPE::EXECUTE_RC, PRIVILEGE3, GRANULARITY_4K, SIZE_32b);
	gdt[5] = CreateSegmentDescriptor((uintptr_t)execFileBaseAddress, 0xFFFF, DESCRIPTOR_TYPE::DATA_RW, PRIVILEGE3, GRANULARITY_4K, SIZE_32b);
	// The pushed data on the stack must follow the reverse order of the pop in the iret algorithm

	asm volatile(
		"cli\n"
		"xchg %%bx, %%bx\n"
		"push %[userSS]\n"	   // POP SS
		"push %[userESP]\n"	   // POP ESP
		"push %[userEFLAGS]\n" // POP EFLAGS
		"push %[userCS]\n"	   // POP CS
		"push %[userEIP]\n"	   // POP EIP
		"movw %[userDS], %%ax\n"
		"movw %%ax, %%ds\n"
		"movw %%ax, %%es\n"
		"movw %%ax, %%fs\n"
		"movw %%ax, %%gs\n"
		// "movw %%ax, %%ds\n"
		"iret\n"
		: /* outputs */
		: [userSS] "irm"((uint32_t)CreateSegmentSelector(6, PRIVILEGE3)), [userESP] "i"((uint32_t)4000), [userEFLAGS] "i"((uint32_t)0), [userCS] "irm"((uint32_t)CreateSegmentSelector(4, PRIVILEGE3)), [userEIP] "m"((uint32_t)linearAddress), [userDS] "irm"(CreateSegmentSelector(5, PRIVILEGE3)) : "ax");
}

extern "C" void PrepareProtected(void)
{
	// From intel doc the first entry in the GDT must be 0
	gdt[0].uival = 0;
	// kernel code
	gdt[1] = CreateSegmentDescriptor(0, 0xFFFFF, DESCRIPTOR_TYPE::EXECUTE_R, PRIVILEGE0, GRANULARITY_4K, SIZE_32b);
	// kernel data
	gdt[2] = CreateSegmentDescriptor(0, 0xFFFFF, DESCRIPTOR_TYPE::DATA_RW, PRIVILEGE0, GRANULARITY_4K, SIZE_32b);
	// kernel stack need to be created depending on the available memory
	gdt[3] = CreateSegmentDescriptor(0, 0xFFFFF, DESCRIPTOR_TYPE::DATA_RW, PRIVILEGE0, GRANULARITY_4K, SIZE_32b);

	// user code
	gdt[4].uival = 0;
	// user data
	gdt[5].uival = 0;
	// user stack needs to be created depending on the available memory
	gdt[6] = CreateSegmentDescriptor(0, 0xFFFFF, DESCRIPTOR_TYPE::DATA_RW, PRIVILEGE3, GRANULARITY_4K, SIZE_32b);
}
