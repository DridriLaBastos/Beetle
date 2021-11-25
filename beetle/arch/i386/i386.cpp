#include <stdint.h>
#include <beetle/arch.hpp>

#include "include/port.hpp"
#include "include/protected.hpp"
#include "include/descriptor.hpp"
#include "include/interrupts.hpp"

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

union GateDescriptor
{
	uint64_t intValue;
	struct { uint64_t offset1:16,selector:16,:8,type:5,dpl:2,p:1,offset2:16; };
};

static uint64_t createTaskGate (const uint16_t selector, const unsigned int dpl, const bool present)
{
	GateDescriptor gate;

	gate.selector = selector;
	gate.type = ARCH::I386::TG;
	gate.dpl = dpl;
	gate.p = present;
	return gate.intValue;
}

static uint64_t createInterruptGate (const uint32_t offset, const uint16_t segmentSelector, const unsigned int dpl, const bool present)
{
	GateDescriptor gate;
	gate.offset1 = offset & 0xFFFF;
	gate.selector = segmentSelector;
	gate.type = ARCH::I386::IG_32;
	gate.dpl = dpl;
	gate.p = present;
	gate.offset2 = offset >> 16;
	
	return gate.intValue & ~(((uint64_t)0b111) << 37);
}

static uint64_t createTrapGate (const uint32_t offset, const uint16_t segmentSelector, const unsigned int dpl, const bool present)
{
	GateDescriptor gate;
	gate.offset1 = offset & 0xFFFF;
	gate.selector = segmentSelector;
	gate.type = ARCH::I386::TG_32;
	gate.dpl = dpl;
	gate.p = present;
	gate.offset2 = offset >> 16;
	
	return gate.intValue & ~(((uint64_t)0b111) << 37);
}

static uint64_t createNullGate(void) { return 0; }

static void initSystemInt(void)
{
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDE,0x8,ARCH::I386::PRIVILEGE0,1),0);
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDB,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNMI,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBP,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptOF,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptBR,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptUD,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNM,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptDF,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptCS,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptTS,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptNP,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptSS,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptGP,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptPF,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createNullGate());
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMF,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptAC,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptMC,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptXM,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::interruptVE,0x8,ARCH::I386::PRIVILEGE0,1));
}

static void initPICInt(void)
{
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq0,0x8,ARCH::I386::PRIVILEGE0,1), 0xB0);
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq1,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq2,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq3,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq4,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq5,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq6,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq7,0x8,ARCH::I386::PRIVILEGE0,1));

	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq8,0x8,ARCH::I386::PRIVILEGE0,1), 0xC0);
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq9,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createNullGate());
	IDT::push(createNullGate());
	IDT::push(createNullGate());
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq13,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createInterruptGate((uint32_t)ARCH::I386::irq14,0x8,ARCH::I386::PRIVILEGE0,1));
	IDT::push(createNullGate());
}

static void configurePICs()
{
	//Configuration of the master PIC
	outb(PIC_ICW1, 0x20);
	outb(PIC1_ICW2, 0x21);
	outb(PIC1_ICW3, 0x21);
	outb(PIC1_ICW4, 0x20);

	//Configuration os the slave PIC
	outb(PIC_ICW1, 0xA1);
	outb(PIC2_ICW2, 0xA0);
	outb(PIC2_ICW3, 0xA0);
	outb(PIC2_ICW4, 0xA0);
}

static void enablePICs(void)
{
	outb(~0,0x21);
	outb(~0,0xA1);
}

static void initInt()
{
	initSystemInt();
	initPICInt();
	ARCH::I386::IDT::load();
	configurePICs();
	enablePICs();
}

void ARCH::init()
{
	initInt();
}

void __attribute__((noreturn)) ARCH::endlessLoop()
{
	while (true)
	{
		//asm ("xchg %bx, %bx");
		asm ("hlt");
	}
}