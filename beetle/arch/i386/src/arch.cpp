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

static TSS tss;

//Those symbols need to be accessible from assembly file preinit.s
extern "C" {
	descriptor_t gdt[16] __attribute__((aligned(64))) =
	{
		0,//Intel documentation : first entry in GDT mus be null
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::EXECUTE_R,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel code
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel data
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE0,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//Kernel stack

		0,
		//CreateTSSDescriptor((uint32_t)&tss,sizeof(tss)-1,4,0,DESCRIPTOR::SIZE_32b),

		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::EXECUTE_R,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//User code segment
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b),//User data segment
		CreateSegmentDescriptor(0,0xFFFFFFFF,DESCRIPTOR::DATA_RW,DESCRIPTOR::PRIVILEGE3,DESCRIPTOR::GRANULARITY_4K,DESCRIPTOR::SIZE_32b) //User stack
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
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDE,0x8,ARCH::I386::PRIVILEGE0,1),0);
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDB,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNMI,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBP,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptOF,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBR,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptUD,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNM,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDF,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptCS,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptTS,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNP,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptSS,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptGP,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptPF,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createNullGate());
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMF,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptAC,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMC,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptXM,0x8,ARCH::I386::PRIVILEGE0,1));
	// IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptVE,0x8,ARCH::I386::PRIVILEGE0,1));

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

void ARCH::init()
{
	//Enable caching
	__asm__("movl %%cr0, %%eax\n"
			"andl $~0x60000000, %%eax\n"
			"movl %%eax, %%cr0\n" :::"eax");

	gdt[4] = CreateTSSDescriptor((uint32_t)&tss,sizeof(tss)-1,4,0,DESCRIPTOR::SIZE_32b);

	// Fill the static values of the tss to describe the values for the current kernel task
	//TODO: is it needed to also change version 1 and 2 of the ss and esp fields ?
	__asm__("mov %%cr3, %%eax\n"
		"movl %%eax, %0\n"
		"movl %%esp, %1\n"
		"movw %%ss, %2\n"
		"movw $0, %3\n"::
		"m"(tss.cr3), "m" (tss.esp0), "m" (tss.ss0), "m"(tss.iomap):
		"eax");

	//Change the ltr register to contain the selector for the kernel task
	__asm__("movw %0, %%ax\n"
			"ltr %%ax\n"::"i"(4 << 3) : "ax");

	//gdt_info.descriptors = gdt;
	//gdt_info.count = 1;
	//idt_info.descriptors = idt;
	//idt_info.count = 0;

	initInt();
}

void __attribute__((noreturn)) ARCH::endlessLoop()
{
	while (true)
	{
		//asm ("xchg %bx, %bx");
		__asm__ ("hlt");
	}
}

/**
 * On x86 transferring execution to user land means jumping from a priviledged code segment to an unprivileged one.
 */
void ARCH::moveToUserLand(const uint32_t logicalAddress)
{
	const unsigned int codeSegmentDescriptor = (4 << 3) + 3;
	const unsigned int dataSegmentGDTIndex   = (5 << 3) + 3;
	const unsigned int stackSegmentGDTIndex  = (6 << 3) + 3;

	__asm__(
			"mov %0, %%eax\n"
			"mov %%ax, %%ds\n"
			"mov %%ax, %%es\n"
			"mov %%ax, %%fs\n"
			"mov %%ax, %%gs\n"

			"mov %1, %%ax\n"
			"mov %%ax, %%ss\n": /*no output*/ : "i" (dataSegmentGDTIndex), "i" (stackSegmentGDTIndex) : "eax");
}
