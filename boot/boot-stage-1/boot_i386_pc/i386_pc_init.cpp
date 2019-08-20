#include "arch/i386/i386.hpp"

#define DEBUG

#define ASM(a) __asm__ volatile (a)

#define NOP ASM("nop")
#define HLT ASM("hlt")

void init_gdt  (ARCH::I386::GDT& gdt);
void init_idt  (ARCH::I386::IDT& idt);
void init_apic (void);

extern "C" 
{
	void interrupt_DE	(void);
	void interrupt_DB	(void);
	void interrupt_NMI	(void);
	void interrupt_BP	(void);
	void interrupt_OF	(void);
	void interrupt_BR	(void);
	void interrupt_UP	(void);
	void interrupt_NM	(void);
	void interrupt_DF	(void);
	void interrupt_CSO	(void);
	void interrupt_TS	(void);
	void interrupt_NP	(void);
	void interrupt_SS	(void);
	void interrupt_GP	(void);
	void interrupt_PF	(void);
	void interrupt_IR	(void);
	void interrupt_MF	(void);
	void interrupt_AC	(void);
	void interrupt_MC	(void);
	void interrupt_XM	(void);
	void interrupt_VE	(void);
	void interrupt_IRQ0	(void);
}

extern "C" void init(const unsigned int multibootInfoStructureAddr)
{
	ARCH::I386::GDT gdt (0x1000,512);
	ARCH::I386::IDT idt (0x500, 256);
	ARCH::I386::APIC apic;

	/* Initialize the new GDT */
	init_gdt(gdt);

	/* Initialize the new IDT */
	init_idt(idt);

	idt.makeCurrent();
	apic.setTimerDivideValue(ARCH::I386::APIC::TIMER_DIVIDE_VALUE::D1);
}

void init_gdt (ARCH::I386::GDT& gdt)
{
	constexpr unsigned int SSBASE = 0x2000;
	// adding two admin segments + the kernel stack
	gdt.addSegmentDescriptor(0, 0xFFFFF, ARCH::I386::C_EO, PRESENT | PRIVILEGE0, EXEC_32B | LIMIT_4K);
	gdt.addSegmentDescriptor(0, 0xFFFFF, ARCH::I386::D_RW, PRESENT | PRIVILEGE0, EXEC_32B | LIMIT_4K);
	gdt.addSegmentDescriptor(SSBASE, 0x80000 - SSBASE - 1,ARCH::I386::D_RW, PRESENT | PRIVILEGE0, STACK_32B | LIMIT_BYTES);

	gdt.makeCurrent();
	gdt.select(ARCH::I386::SEGMENT_NAMES::DS, 2, 0);
	gdt.select(ARCH::I386::SEGMENT_NAMES::FS, 0, 0);
	gdt.select(ARCH::I386::SEGMENT_NAMES::GS, 0, 0);
	gdt.select(ARCH::I386::SEGMENT_NAMES::ES, 0, 0);
	//gdt.select(ARCH::I386::SEGMENT_NAMES::SS, 3, 0);
}

void init_idt (ARCH::I386::IDT& idt)
{
	//Shuting down the pic
	__asm__ (
	"movb $0xFF, %al\n"
	"outb %al, $0xA1\n"
	"outb %al, $0x21\n");

	//Initializing IDT descriptors
	idt.addInterruptGateDescriptor((unsigned)interrupt_DE,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_DB,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_NMI, 0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_BP,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_OF,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_BR,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_UP,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_NM,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_DF,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_CSO, 0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_TS,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_NP,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_SS,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_GP,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_PF,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_IR,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_MF,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_AC,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_MC,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_XM,  0x8, PRESENT | PRIVILEGE0);
	idt.addInterruptGateDescriptor((unsigned)interrupt_VE,  0x8, PRESENT | PRIVILEGE0);

	for (unsigned i = idt.getCount(); i < 32; ++i)
		idt.addInterruptGateDescriptor(0,0x8,NOT_PRESENT);
}