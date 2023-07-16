#include <string.h>

#include "beetle/arch.hpp"

#include "i386.hpp"

#define PIC_ICW1_ICW4_NEEDED 1
#define PIC_ICW1_SINGLE_MODE (0 << 1) //Two PICs are present
#define PIC_ICW1_CALL_ADDRESS_INTERVAL (0 << 2) //Unused by the PIC in 8086 mode, the 5 upper bits will forms the interrupt address
#define PIC_ICW1_LEVEL_TRIGGERED_MODE (0 << 3) //level triggered mode not supported by bochs
#define PIC_ICW1 (1 << 4) | PIC_ICW1_LEVEL_TRIGGERED_MODE | PIC_ICW1_CALL_ADDRESS_INTERVAL | PIC_ICW1_SINGLE_MODE | PIC_ICW1_ICW4_NEEDED

#define PIC1_ICW2 0xC0 //The interrupts from the master PIC go from 0xB0 to 0xB7
#define PIC2_ICW2 0xD0 //The interrupts from the slave  PIC go from 0xC0 to 0xC7

#define PIC1_ICW3 (1 << 2) //Slave on irq line 2
#define PIC2_ICW3 2 //The slave pic is connected to irq 2 on the master

#define PIC_ICW4_8086MODE 1
#define PIC_ICW4_AUTO_EOI (1 << 1)
#define PIC1_ICW4_BUFFERED_MODE (0b10 << 2) //Buffered mode master
#define PIC2_ICW4_BUFFERED_MODE (0b11 << 2) //Buffered mode slave
#define PIC_ICW4_FN_MODE (0 << 4) //Not special fully nested mode
#define PIC1_ICW4 PIC_ICW4_FN_MODE | PIC_ICW4_FN_MODE | PIC1_ICW4_BUFFERED_MODE | PIC_ICW4_AUTO_EOI | PIC_ICW4_8086MODE
#define PIC2_ICW4 PIC_ICW4_FN_MODE | PIC_ICW4_FN_MODE | PIC2_ICW4_BUFFERED_MODE | PIC_ICW4_AUTO_EOI | PIC_ICW4_8086MODE

using namespace ARCH::I386;

struct tdescriptor {
	uint16_t count;
	uint32_t base;
} __attribute__((packed));

struct FarPointer
{
	uint32_t offset;
	uint16_t selector;
} __attribute__((packed));

//Those symbols need to be accessible from assembly file preinit.s
extern "C" {
	descriptor_t gdt[16] __attribute__((aligned(64))) =
	{
		0,//Intel documentation : first entry in GDT mus be null
		//Conforming code segment because we want the CPL to change when transferring program to the cose segments
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::EXECUTE_R,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel code
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel data
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel stack

		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::EXECUTE_R,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//User code segment
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//User data segment
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b), //User stack
	};
	descriptor_t idt[256] __attribute__((aligned(64)));

	SystemTableRegisterDescription gdtr { .limit=sizeof(gdt), .linearBaseAddress=(uint32_t)gdt };
	SystemTableRegisterDescription idtr { .limit=sizeof(idt), .linearBaseAddress=(uint32_t)idt };
}

// union GateDescriptor
// {
// 	uint64_t intValue;
// 	struct { uint64_t offset1:16,selector:16,:8,type:5,dpl:2,p:1,offset2:16; };
// };

// static uint64_t createTaskGate (const uint16_t selector, const unsigned int dpl, const bool present)
// {
// 	GateDescriptor gate;

// 	gate.selector = selector;
// 	gate.type = ARCH::I386::TG;
// 	gate.dpl = dpl;
// 	gate.p = present;
// 	return gate.intValue;
// }

// static uint64_t createInterruptGate (const uint32_t offset, const uint16_t segmentSelector, const unsigned int dpl, const bool present)
// {
// 	GateDescriptor gate;
// 	gate.offset1 = offset & 0xFFFF;
// 	gate.selector = segmentSelector;
// 	gate.type = ARCH::I386::IG_32;
// 	gate.dpl = dpl;
// 	gate.p = present;
// 	gate.offset2 = offset >> 16;
	
// 	return gate.intValue & ~(((uint64_t)0b111) << 37);
// }

// static uint64_t createTrapGate (const uint32_t offset, const uint16_t segmentSelector, const unsigned int dpl, const bool present)
// {
// 	GateDescriptor gate;
// 	gate.offset1 = offset & 0xFFFF;
// 	gate.selector = segmentSelector;
// 	gate.type = ARCH::I386::TG_32;
// 	gate.dpl = dpl;
// 	gate.p = present;
// 	gate.offset2 = offset >> 16;
	
// 	return gate.intValue & ~(((uint64_t)0b111) << 37);
// }

// static uint64_t createNullGate(void) { return 0; }

static void initInt()
{
	/* Initialisation of système interruptions */
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDE,0x8,ARCH::I386::PRIVILEGE0,1),0);
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDB,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNMI,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBP,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptOF,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBR,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptUD,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNM,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDF,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptCS,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptTS,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNP,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptSS,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptGP,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptPF,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createNullGate());
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMF,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptAC,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMC,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptXM,0x8,ARCH::I386::PRIVILEGE0,1));
//	 IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptVE,0x8,ARCH::I386::PRIVILEGE0,1));

	// /* Initialization of PIC interruptions */
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq0,0x8,ARCH::I386::PRIVILEGE0,1), 0xB0);
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq1,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq2,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq3,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq4,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq5,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq6,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq7,0x8,ARCH::I386::PRIVILEGE0,1));

	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq8,0x8,ARCH::I386::PRIVILEGE0,1), 0xC0);
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq9,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createNullGate());
	// IDT::push(createNullGate());
	// IDT::push(createNullGate());
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq13,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq14,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createNullGate());

	/* Making the configured IDT the current IDT */
	// IDT::load();

	/* Configuration of the PICs */
	/** Configuration of the master PIC **/
	outb(PIC_ICW1, 0x20);
	outb(PIC1_ICW2, 0x21);
	outb(PIC1_ICW3, 0x21);
	outb(PIC1_ICW4, 0x20);

	/** Configuration os the slave PIC **/
	outb(PIC_ICW1, 0xA1);
	outb(PIC2_ICW2, 0xA0);
	outb(PIC2_ICW3, 0xA0);
	outb(PIC2_ICW4, 0xA0);

	/* Enabling the PICs */
	outb(~0,0x21);
	outb(~0,0xA1);
}

static TSS kernelTss;
static TSS userTss;

struct DescriptorTableInfo
{
	ARCH::I386::descriptor_t* descriptors;
	size_t index;
};

static DescriptorTableInfo GDTInfo;

static size_t appendDescriptor(DescriptorTableInfo& descriptorTable, const descriptor_t& descriptor)
{
	const size_t insertIndex = descriptorTable.index;
	descriptorTable.descriptors[insertIndex] = descriptor;
	descriptorTable.index += 1;
	return insertIndex;
}

void ARCH::init()
{
	GDTInfo.descriptors = gdt;
	GDTInfo.index = 7;
	//x86 first init step is to override the previous TSS and create a new one to store informations
	//for the kernel tak after task switching
	memset(&kernelTss,0,sizeof(kernelTss));

	appendDescriptor(GDTInfo, CreateTSSDescriptor((uintptr_t )&kernelTss,sizeof(kernelTss)-1,DESCRIPTOR::PRIVILEGE0));

	__asm__("movl %%cr3, %%eax\n"
			"movl %%eax, %0\n"
			::"m"(kernelTss.cr3):"eax");

	//preparing the user tss
	memset(&userTss,0,sizeof(userTss));

#if 0

	//Change the ltr register to contain the selector for the kernel task
	__asm__("movw %0, %%ax\n"
			"ltr %%ax\n"::"i"(4 << 3) : "ax");

#endif

	//initInt();
}

void __attribute__((noreturn)) ARCH::endlessLoop()
{
	while (true)
	{
		//asm ("xchg %bx, %bx");
		__asm__ ("hlt");
	}
}

ARCH::task_t ARCH::TASK::task_createUserLand(const void *entryPoint)
{
	//Code segment for task are all non conforming : they can only be accessed by task with a CPL = to the DPL of the
	//segment. They need to be conforming because when switching we want the CPL to change. For the switch to perform
	//when a task use a non-conforming code segment, it is mandatory to pass throught a call gate (a task gate). So
	//when a new task is created two entries are added inside the GDT : a TSS Descriptor that references the TSS and
	//a task-gate descriptor that is pointing to the previous TSS. The value returned is the index of the Task Gate
	//descriptor so when performing a task switch this value can directly be used
	const size_t insertedPos = appendDescriptor(GDTInfo, CreateTSSDescriptor((uintptr_t)&userTss,sizeof(userTss),DESCRIPTOR::PRIVILEGE3));

	const unsigned int taskSelector = DESCRIPTOR::SEGMENT_SELECTOR(insertedPos,DESCRIPTOR::PRIVILEGE3);
	//Only code in priviledge level 0 are authorized to access code segment from a task switch
	const size_t taskOpaqueDescriptor = appendDescriptor(GDTInfo, CreateTaskSwitchDescriptor(taskSelector,DESCRIPTOR::PRIVILEGE0));

	memset(&userTss,0,sizeof(userTss));

	userTss.cs = DESCRIPTOR::SEGMENT_SELECTOR(4,DESCRIPTOR::PRIVILEGE3);
	userTss.ds = DESCRIPTOR::SEGMENT_SELECTOR(5,DESCRIPTOR::PRIVILEGE3);
	userTss.ss = DESCRIPTOR::SEGMENT_SELECTOR(6,DESCRIPTOR::PRIVILEGE3);
	userTss.es = userTss.ds;
	userTss.fs = userTss.ds;
	userTss.gs = userTss.ds;
	userTss.esp = 0x2000000;
	userTss.eip = (uintptr_t)entryPoint;

	//__asm__("xchg %%bx,%%bx\n"
	//		"movl %0, %%eax\n" :: "i"(&userTss) : "eax");

	return taskOpaqueDescriptor;
}

void ARCH::TASK::task_switch(const task_t t)
{
	FarPointer ptr;
	ptr.selector = (gdt[t] >> 16) & 0xFFFF;
	//TODO: Can this offset be 0 ?
	ptr.offset = 0;

	__asm__("xchg %%bx, %%bx\n"
			"ljmp *%0" ::"m"(ptr): "ax");
}
