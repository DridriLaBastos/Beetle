#include "arch/i386/i386.hpp"

#undef DEBUG

#ifdef DEBUG
    #define BDG __asm__ volatile ("xchg %bx, %bx");
#else
    #define BDG
#endif

extern "C" 
{
    void default_int(void);
    void gp_int (void);
    void ss_int (void);
    void np_int (void);
    void pf_int (void);
    void ac_int (void);
    void ud_int (void);
}

// boot-stage-1 main function
extern "C" void boot_stage_1_main (void)
{
    CPU::I386::IDT idt;
    CPU::I386::GDT gdt;

    for (unsigned int i = 0; i < 32; ++i)
    {
        idt.add(CPU::I386::create_interruptgate_descriptor((uint32_t)default_int, 0x08, PRESENT | PRIVILEGE0));
    }

    /* adding two flat segments */
    gdt.add(CPU::I386::create_segment_descriptor(0, 0xFFFFF, CPU::I386::C_ER, PRESENT | PRIVILEGE0 | CODE_DATA, 0b1100));
    gdt.add(CPU::I386::create_segment_descriptor(0, 0xFFFFF, CPU::I386::D_RW, PRESENT | PRIVILEGE0 | CODE_DATA, 0b1100));

    gdt.makeCurrent();

    gdt.select(CPU::I386::SEGMENT_NAMES::DS, 2, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::ES, 0, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::GS, 0, 0);
    gdt.select(CPU::I386::SEGMENT_NAMES::FS, 0, 0);

    /* idt set after the segments are ignitialized */
    idt.makeCurrent();

    // TODO: figure out why an interrupt is emited once here
    BDG;
    for(;;);
}
