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

extern "C" 
{
    void interrupt_DE (void);
    void interrupt_DB (void);
    void interrupt_NMI (void);
    void interrupt_BP (void);
    void interrupt_OF (void);
    void interrupt_BR (void);
    void interrupt_UP (void);
    void interrupt_NM (void);
    void interrupt_DF (void);
    void interrupt_CSO (void);
    void interrupt_TS (void);
    void interrupt_NP (void);
    void interrupt_SS (void);
    void interrupt_GP (void);
    void interrupt_PF (void);
    void interrupt_IR (void);
    void interrupt_MF (void);
    void interrupt_AC (void);
    void interrupt_MC (void);
    void interrupt_XM (void);
    void interrupt_VE (void);
}

// boot-stage-1 main function
extern "C" void boot_stage_1_main (void)
{
    CPU::I386::IDT idt;
    CPU::I386::GDT gdt;

    // adding two flat segments
    gdt.add(CPU::I386::create_segment_descriptor(0, 0xFFFFF, CPU::I386::C_ER, PRESENT | PRIVILEGE0 | CODE_DATA, 0b1100));
    gdt.add(CPU::I386::create_segment_descriptor(0, 0xFFFFF, CPU::I386::D_RW, PRESENT | PRIVILEGE0 | CODE_DATA, 0b1100));

    gdt.makeCurrent();

    gdt.select(CPU::I386::SEGMENT_NAMES::DS, 2, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::FS, 0, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::GS, 0, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::SS, 2, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::ES, 0, 0);

    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_DE,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_DB,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_NMI, 0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_BP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_OF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_BR,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_UP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_NM,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_DF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_CSO, 0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_TS,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_NP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_SS,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_GP,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_PF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_IR,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_MF,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_AC,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_MC,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_XM,  0x8, PRESENT | PRIVILEGE0));
    idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)interrupt_VE,  0x8, PRESENT | PRIVILEGE0));

    // TODO: figure out why an interrupt is emited here
    BDG;
    idt.makeCurrent();

    BDG;
    for(;;);
}