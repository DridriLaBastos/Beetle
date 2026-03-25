#include <stdint.h>

#include <beetle/arch.hpp>

#include "i386.hpp"

#define PIC_EOI 0x20
#define MASTER_PIC_PORT 0x20
#define SLAVE_PIC_PORT  0xA0

static uint64_t CMOSRealTimeClockCount = 0;

void ARCH::I386::interruptDE  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptDB  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNMI (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptBP  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptOF  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptBR  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptUD  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNM  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptDF  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptCS  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptTS  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNP  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptSS  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptGP  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptPF  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptMF  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptAC  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptMC  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptXM  (const void*, const int) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptVE  (const void*, const int) { asm("xchg %bx, %bx"); }

/**
 * Stack when calling this function:
 * SS
 * ESP
 * EFLAGS
 * CS
 * EIP
 */
void ARCH::I386::irq0 (const void*)
{
    // __asm__ volatile(
    //     "pushd eax\n"
    //     "pushd ebx\n"
    //     "pushd ecx\n"
    //     "pushd edx\n"
    //     "pushd edi\n"
    //     "pushd esi\n"
    //     "pushd ebp\n"
    //     "movzd eax"
    // );
    outb(PIC_EOI,MASTER_PIC_PORT);
}

void ARCH::I386::irq1 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq2 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq3 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq4 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq5 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq6 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq7 (const void*) { outb(PIC_EOI,MASTER_PIC_PORT); }

void ARCH::I386::irq8 (const void*) { CMOSRealTimeClockCount += 1; outb(PIC_EOI, SLAVE_PIC_PORT); outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq9 (const void*) { outb(PIC_EOI, SLAVE_PIC_PORT); outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq13 (const void*) { outb(PIC_EOI, SLAVE_PIC_PORT); outb(PIC_EOI,MASTER_PIC_PORT); }
void ARCH::I386::irq14 (const void*) { outb(PIC_EOI, SLAVE_PIC_PORT); outb(PIC_EOI,MASTER_PIC_PORT); }