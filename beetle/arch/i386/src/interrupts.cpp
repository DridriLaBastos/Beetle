#include <stdint.h>

#include <beetle/arch.hpp>

#include "i386.hpp"
#include "types.inl"

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
 * SS       (interrupted)
 * ESP      (interrupted)
 * EFLAGS   (interrupted)
 * CS       (interrupted)
 * EIP      (interrupted)
 */
void ARCH::I386::irq0 (void)
{
	__asm__ volatile ("pusha");

	__asm__ volatile ("push %gs");
	__asm__ volatile ("push %fs");
	__asm__ volatile ("push %es");
	__asm__ volatile ("push %ds");

	__asm__ volatile ("push %esp"); // Point to the pushed registers that represent a frame context
	__asm__ volatile ("call Beetle_Api_Schedule");
	__asm__ volatile ("add $4, %esp");

	__asm__ volatile ("pop %ds");
	__asm__ volatile ("pop %es");
	__asm__ volatile ("pop %fs");
	__asm__ volatile ("pop %gs");

	__asm__ volatile ("popa");

	outb(PIC_EOI,MASTER_PIC_PORT);

	__asm__ volatile ("iret");
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