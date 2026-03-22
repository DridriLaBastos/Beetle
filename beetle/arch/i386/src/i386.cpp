#include <stdint.h>

#include <beetle/arch.hpp>

#include "i386.hpp"

#define DBG() __asm__ volatile ("xchg %bx, %bx")

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

union UGateDescriptor {
	descriptor_t uival;

	struct {
		descriptor_t
			offset15_0: 16,
			ss: 16,
			:8,
			type: 5,
			dpl: 2,
			p: 1,
			offset31_16: 16;
	} fields;
};

union UTaskGateOffsetFields
{
	uint32_t uival;

	struct {
			uint16_t offset15_0;
			uint16_t offset31_16;
	} fields;
};

static constexpr UGateDescriptor CreateGateDescriptor (const uint32_t offset, segment_selector_t ss, const DESCRIPTOR_TYPE type, const unsigned int dpl)
{	
	const UTaskGateOffsetFields offsetField { .uival=offset };
	const UGateDescriptor desc = UGateDescriptor{
		.fields = {
			.offset15_0 = offsetField.fields.offset15_0,
			.ss = 8,
			.type = (int)DESCRIPTOR_TYPE::SYSTEM_32b_IG,
			.p = 1,
			.offset31_16 = offsetField.fields.offset31_16
		}
	};

	return desc;
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

// See https://wiki.osdev.org/Serial_Ports#Programming_the_Serial_Communications_Port
static void InitSerial()
{
	ARCH::I386::outb(0x00,COM1_BASE + 1); 	// Disable all interrupts
   	ARCH::I386::outb(0x80,COM1_BASE + 3);	// Enable DLAB (set baud rate divisor)
   	ARCH::I386::outb(0x01,COM1_BASE + 0);	// Set divisor to 1 (lo byte) 115200 baud
   	ARCH::I386::outb(0x00,COM1_BASE + 1);	//                  (hi byte)
   	ARCH::I386::outb(0x03,COM1_BASE + 3);	// 8 bits, no parity, one stop bit, DLAB off
	ARCH::I386::outb(0b11000111,COM1_BASE + 2);	// Enable FIFO, clear them, with 14-byte threshold
	ARCH::I386::outb(0b00010011,COM1_BASE + 4); // IRQs disabled, RTS/DSR set
												// loopback to test the configurations
	ARCH::I386::outb(0xAE,COM1_BASE + 0); // Test serial chip (send byte 0xAE and check if serial returns same byte)

   	ARCH::I386::outb(0x1E,COM1_BASE + 4);    // Set in loopback mode, test the serial chip

	uint8_t status;

	do 
	{
		status = ARCH::I386::inb(COM1_BASE + 5);
	} while (!(ARCH::I386::inb(COM1_BASE+5) & 0b11111));

	if (status & 0b1) {
		// If data can be read and the sent data has been received, the loop back mode is disabled
		const uint8_t data = ARCH::I386::inb(COM1_BASE + 0);

		if (data == 0xAE) {
			ARCH::I386::outb(0b00000111,COM1_BASE + 4);
		} else {
			__asm__ volatile ("xchg %bx, %bx\nxchg %ax, %ax");
		}
	} else {
		__asm__ volatile ("xchg %bx, %bx\n xchg %cx,%cx");
	}
}

void ARCH::Init(void* firstAvailableMemory)
{
	//Sanity checks
	static_assert(sizeof(void*) == sizeof(uint32_t), "Not compiling for i386 architecture : void* is greater than 32bits");
	static_assert(sizeof(uintptr_t) == sizeof(uint32_t), "Not compiling for i386 architecture : uintptr_t is greater than 32bits");

	InitSerial();

	// IRQ from the master interrupt controller are wired into 0x20 to 0x28

	// IRQ from the slave interrupt controller are wired into 0x30 to 0x38

	// Beetle syscall will be wired into 0xBE
}

void ARCH::Isolate()
{
	// Clear interrupt flags ans stop receiving them
	__asm__ ("cli");

	// Isolate both IRQs controller
	__asm__ volatile (
		"mov $0xFF, %%al\n"
		"out %%al, $0x21\n"
		"out %%al, $0xA1\n"
		:::"al"
	);
}

static constexpr uint8_t MakeICW1 (const bool icw4Needed, const bool singleMode)
{
	return 0x10 | (((int)singleMode) << 1) | (((int)icw4Needed) << 0);
}

static constexpr uint8_t MakeICW4 (const bool autoEoi, const bool isMaster)
{
	return 0b00001001 | (((int)isMaster) << 2) | (((int)autoEoi) << 1);
}

void ARCH::Connect()
{
	// Reseting interrupt controllers
	__asm__ volatile 
	(
		/* Putting both PIC in the init sequence */

		"mov %0, %%al\n" 	// Preparing ICW1 PIC1 into al
		"out %%al, $0x20\n"	// out ICW1 PIC1
		"mov %1, %%al\n"	// Preparing ICW1 PIC2 into al
		"out %%al, $0xA0\n"	// out ICW1 PIC2
		
		/* Performing initialization steps */
		/** Sending ICW2 **/

		"mov $0x20, %%al\n" // Preparing ICW2 PIC1 : irqs from master PIC starting at 0x20
		"out %%al, $0x21\n" // out ICW2 PIC1
		"mov $0x30, %%al\n"	// Preparing ICW2 PIC2 : irqs from slave PIC statring at 0x30s
		"out %%al, $0xA1\n"	// out ICW2 PIC2

		/** Sending ICW3 **/
		"mov $0b100, %%al\n"// Preparing Master ICW3 : slave irqs on pin 2
		"out %%al, $0x21\n"	// out ICW3 PIC1
		"mov $2, %%al\n"	// Preparing slave ICW3 : ID 2 -> slave connected on master pin 2
		"out %%al, $0xA1\n"	// out ICW3 PIC2

		/** Sending ICW4 **/
		"mov %2, %%al\n" 	// Preparing ICW4 PIC1 into al
		"out %%al, $0x21\n"	// out ICW1 PIC1
		"mov %3, %%al\n"	// Preparing ICW4 PIC2 into al
		"out %%al, $0xA1\n"	// out ICW1 PIC2

		/* End of initialization steps -> unmasking the PIC */
		// End of initialization from the OS side : strictly speaking, the PICs are fully initialized
		// after receiving the ICW4 command word
		"mov $0, %%al\n"
		"out %%al, $0x21\n"
		"out %%al, $0xA1\n"

		: /*outputs*/
		: /*inputs*/ "i" (MakeICW1(true,false)), "i" (MakeICW1(true,false)), "i" (MakeICW4(false,true)), "i" (MakeICW4(false,false))
		: /*clobbers*/ "eax"

	);

	// Enabling interrupts handling
	__asm__ ("sti");
}

// c linkage needed because the function si called from asm block
__attribute__((naked))
static void SyscallPrepare(void)
{
	//TODO: With optimizations enabled can the compiler detects that the
	// the argument is already in the register and thus not push it ?
	register BEETLE::ESysCallFn syscallFn;
	__asm__ volatile ("movl %%eax, %0\n"
	: /*outputs*/
	: /*inputs*/ "X" (syscallFn));
	BEETLE::API::Syscall(syscallFn);
	__asm__ volatile ("retf");
}

void ARCH::MakeSyscall(const BEETLE::ESysCallFn syscallFn)
{
	struct {
		uint32_t offset;
		uint16_t segment;
	} __attribute__((packed)) longCallPtr { .offset = (uint32_t)(uintptr_t)SyscallPrepare, .segment = 0x8 };
	__asm__ volatile (
		"movl %0, %%eax\n\t"
		"lcall *%1\n\t"
		: /* outputs */
		: /* inputs*/ "X" (static_cast<unsigned int>(syscallFn)), "X" (longCallPtr)
		: /* clobbers */ "eax", "memory"
	);
}

void ARCH::EndlessLoop(void)
{
	while (true)
	{
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


	// idt[0x08] = CreateGateDescriptor((uint32_t)(uintptr_t)ARCH::I386::interruptDF,CreateSegmentSelector(1,0),DESCRIPTOR_TYPE::SYSTEM_32b_IG,0).uival;
	idt[0x20] = CreateGateDescriptor((uint32_t)(uintptr_t)ARCH::I386::irq0,CreateSegmentSelector(1,0),DESCRIPTOR_TYPE::SYSTEM_32b_IG,0).uival;
}

void ARCH::DebugOutput(const char c)
{
	uint8_t status;

	do {
		status = ARCH::I386::inb(COM1_BASE+5);
	} while (!(status & 0b100000));
	ARCH::I386::outb(c,COM1_BASE);
}