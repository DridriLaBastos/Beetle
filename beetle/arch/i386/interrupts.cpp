#include "include/port.hpp"
#include "include/interrupts.hpp"

void ARCH::I386::interruptDE  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptDB  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNMI (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptBP  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptOF  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptBR  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptUD  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNM  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptDF  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptCS  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptTS  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptNP  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptSS  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptGP  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptPF  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptMF  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptAC  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptMC  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptXM  (const void* ptr) { asm("xchg %bx, %bx"); }
void ARCH::I386::interruptVE  (const void* ptr) { asm("xchg %bx, %bx"); }

void ARCH::I386::irq0 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq1 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq2 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq3 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq4 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq5 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq6 (const void* ptr) { outb(0x20,0x20); }
void ARCH::I386::irq7 (const void* ptr) { outb(0x20,0x20); }

void ARCH::I386::irq8 (const void* ptr) { outb(0x20,0x20); outb(0x20, 0xA0); }
void ARCH::I386::irq9 (const void* ptr) { outb(0x20,0x20); outb(0x20, 0xA0); }
void ARCH::I386::irq13 (const void* ptr) { outb(0x20,0x20); outb(0x20, 0xA0); }
void ARCH::I386::irq14 (const void* ptr) { outb(0x20,0x20); outb(0x20, 0xA0); }