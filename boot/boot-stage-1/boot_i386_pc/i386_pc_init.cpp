#include "vga_pc.hpp"
#include "beetle/beetle.hpp"
#include "arch/i386/i386.hpp"

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

/**
 * //TODO: system call must be implemented somewheres
 * Initialization sequence :
 * 	Init CPU core features (GDT/LDT/IDT/paging)
 * 	Init early memory management (malloc and other will be implemented in a process)
 * 	Init process management
 * 	Load a disk driver with the Module from GRUB
 * 	Load an init stage 2 program
 */
//TODO: move the memory management thing in boot stage 2 ?
extern "C" void init(const uint32_t* multibootInfoPtr)
{
	ARCH::I386::GDT gdt (0x1000,512);
	ARCH::I386::IDT idt (0x500, 256);
	ARCH::I386::APIC apic;
	VGA vga;

	/* Initialize the new GDT */
	init_gdt(gdt);

	/* Initialize the new IDT */
	init_idt(idt);

	BEETLE::MemoryManager mm;
	vga.puts("BEETLE - Boot Stage 1\n");

	BEETLE::MULTIBOOT::MultibootHelper mh (multibootInfoPtr);

	if (mh.isFlagSet(BEETLE::MULTIBOOT::MultibootHelper::MODULE))
	{
		vga.putc(mh.getBootmoduleCount() + '0');
		vga.puts(" submodules loaded\n");
		for (unsigned int i = 0; i < mh.getBootmoduleCount(); ++i)
		{
			BEETLE::MULTIBOOT::ModuleInfo* moduleInfo = mh.getBootModuleInfo(i);
			vga.puts(moduleInfo->modString);
			vga.putc('\n');
		}
	}
	else
	{
		vga.puts(mh.getBootmoduleCount() == 0 ? "No bootmodule loaded" : "ERROR");
		vga.putc('\n');
		//Error: we need multiboot module to continue the boot process
	}
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
	
	idt.makeCurrent();
}

#include "beetle/beetle.cpp"
