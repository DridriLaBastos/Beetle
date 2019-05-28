#include "beetle/include/system.hpp"
#include "arch/i386/i386.hpp"

#define DEBUG

#define ASM(a) __asm__ volatile (a)

#ifdef DEBUG
    #define BDG ASM ("xchg %bx, %bx")
#else
    #define BDG
#endif

#define NOP ASM("nop")
#define HLT ASM("hlt")

using namespace ARCH::I386;

void init_gdt  (GDT&);
void init_idt  (IDT&);
void init_apic (void);


extern "C" 
{
    void interrupt_DE   (void);
    void interrupt_DB   (void);
    void interrupt_NMI  (void);
    void interrupt_BP   (void);
    void interrupt_OF   (void);
    void interrupt_BR   (void);
    void interrupt_UP   (void);
    void interrupt_NM   (void);
    void interrupt_DF   (void);
    void interrupt_CSO  (void);
    void interrupt_TS   (void);
    void interrupt_NP   (void);
    void interrupt_SS   (void);
    void interrupt_GP   (void);
    void interrupt_PF   (void);
    void interrupt_IR   (void);
    void interrupt_MF   (void);
    void interrupt_AC   (void);
    void interrupt_MC   (void);
    void interrupt_XM   (void);
    void interrupt_VE   (void);
    void interrupt_IRQ0 (void);
}

void BEETLE::SYSTEM::init()
{
	ARCH::I386::GDT gdt;
	ARCH::I386::IDT idt;

	/* Initialize the new GDT */
    init_gdt(gdt);

	/* Initialize the new IDT */
	init_idt(idt);

    /* Initializing the local APIC if present */
    init_apic();

    idt.makeCurrent();
}

void init_gdt (ARCH::I386::GDT& gdt)
{
    // adding two admin segments
    gdt.add(ARCH::I386::create_segment_descriptor(0, 0xFFFFF, ARCH::I386::C_ER, PRESENT | PRIVILEGE0, G_DB_L_AVL(1,1,0,0)));
    gdt.add(ARCH::I386::create_segment_descriptor(0, 0xFFFFF, ARCH::I386::D_RW, PRESENT | PRIVILEGE0, G_DB_L_AVL(1,1,0,0)));

	gdt.makeCurrent();

	gdt.select(ARCH::I386::SEGMENT_NAMES::DS, 2, 0);
    gdt.select(ARCH::I386::SEGMENT_NAMES::FS, 0, 0);
    gdt.select(ARCH::I386::SEGMENT_NAMES::GS, 0, 0);
    gdt.select(ARCH::I386::SEGMENT_NAMES::SS, 2, 0);
    gdt.select(ARCH::I386::SEGMENT_NAMES::ES, 0, 0);
}

void init_idt (ARCH::I386::IDT& idt)
{
    //Shuting down the pic
    __asm__ (
        "movb $0xFF, %al\n"
        "outb %al, $0xA1\n"
        "outb %al, $0x21\n");

    //Initializing IDT descriptors
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_DE,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_DB,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_NMI, 0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_BP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_OF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_BR,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_UP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_NM,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_DF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_CSO, 0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_TS,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_NP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_SS,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_GP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_PF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_IR,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_MF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_AC,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_MC,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_XM,  0x8, PRESENT | PRIVILEGE0));
    idt.add(ARCH::I386::create_interruptgate_descriptor((uint32_t)interrupt_VE,  0x8, PRESENT | PRIVILEGE0));

    for (unsigned i = idt.get_count(); i < 32; ++i)
        idt.add(ARCH::I386::create_interruptgate_descriptor(0,0x8,NO_PRESENT));
}

void init_apic (void)
{
    /* Checking for presence of a local APIC */
    ARCH::I386::CPUID c (ARCH::I386::CPUID::FUNCTIONS::ONE);

    if (!c.getBitValue(9,c.result.edx))
    {
        //Use the pic instead, but nowadayw every intel processor should have a local APIC
        __asm__ ("mov $0xBACE, %eax");//Beetle ApiC Error for debugging purpose
    }
    else
    {
        /* Initialization of the IVT */
        BDG;
        ARCH::I386::LOCAL_APIC::read_version();
    }
}