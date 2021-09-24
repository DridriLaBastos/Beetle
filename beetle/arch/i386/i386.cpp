#include <stdint.h>
#include <beetle/arch.hpp>

#include "include/descriptor.hpp"
#include "include/interrupts.hpp"

extern "C" unsigned int idtBase;

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

static void initSystemInt(void)
{
	uint64_t* idt = (uint64_t*)idtBase;
	unsigned int index = 0;

	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptDE,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptDB,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptNMI,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptBP,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptOF,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptBR,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptUD,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptNM,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptDF,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptCS,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptTS,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptNP,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptSS,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptGP,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptPF,0x8,ARCH::I386::PRIVILEGE0,1);
	index += 1;//Interrupt vector 15 is unused and reserved by intel
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptMF,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptAC,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptMC,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptXM,0x8,ARCH::I386::PRIVILEGE0,1);
	idt[index++] = createInterruptGate((uint32_t)ARCH::I386::interruptVE,0x8,ARCH::I386::PRIVILEGE0,1);
	
	asm ("lidt idtr");
	asm ("sti");
}

void ARCH::init()
{
	initSystemInt();
}

void __attribute__((noreturn)) ARCH::endlessLoop()
{
	while (true)
	{
		asm ("xchg %bx, %bx");
		asm ("hlt");
	}
}