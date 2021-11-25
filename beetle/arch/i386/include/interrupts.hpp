#ifndef __I386_INTERRUPTS_HPP__
#define __I386_INTERRUPTS_HPP__

namespace ARCH::I386
{
	__attribute__((interrupt)) void interruptDE  (const void* ptr);
	__attribute__((interrupt)) void interruptDB  (const void* ptr);
	__attribute__((interrupt)) void interruptNMI (const void* ptr);
	__attribute__((interrupt)) void interruptBP  (const void* ptr);
	__attribute__((interrupt)) void interruptOF  (const void* ptr);
	__attribute__((interrupt)) void interruptBR  (const void* ptr);
	__attribute__((interrupt)) void interruptUD  (const void* ptr);
	__attribute__((interrupt)) void interruptNM  (const void* ptr);
	__attribute__((interrupt)) void interruptDF  (const void* ptr);
	__attribute__((interrupt)) void interruptCS  (const void* ptr);
	__attribute__((interrupt)) void interruptTS  (const void* ptr);
	__attribute__((interrupt)) void interruptNP  (const void* ptr);
	__attribute__((interrupt)) void interruptSS  (const void* ptr);
	__attribute__((interrupt)) void interruptGP  (const void* ptr);
	__attribute__((interrupt)) void interruptPF  (const void* ptr);
	__attribute__((interrupt)) void interruptMF  (const void* ptr);
	__attribute__((interrupt)) void interruptAC  (const void* ptr);
	__attribute__((interrupt)) void interruptMC  (const void* ptr);
	__attribute__((interrupt)) void interruptXM  (const void* ptr);
	__attribute__((interrupt)) void interruptVE  (const void* ptr);
	 
	__attribute__((interrupt)) void irq0 (const void* ptr);
	__attribute__((interrupt)) void irq1 (const void* ptr);
	__attribute__((interrupt)) void irq2 (const void* ptr);
	__attribute__((interrupt)) void irq3 (const void* ptr);
	__attribute__((interrupt)) void irq4 (const void* ptr);
	__attribute__((interrupt)) void irq5 (const void* ptr);
	__attribute__((interrupt)) void irq6 (const void* ptr);
	__attribute__((interrupt)) void irq7 (const void* ptr);

	__attribute__((interrupt)) void irq8 (const void* ptr);
	__attribute__((interrupt)) void irq9 (const void* ptr);
	//__attribute__((interrupt)) void irq10 (const void* ptr); reserved
	//__attribute__((interrupt)) void irq11 (const void* ptr); reserved
	//__attribute__((interrupt)) void irq12 (const void* ptr); reserved
	__attribute__((interrupt)) void irq13 (const void* ptr);
	__attribute__((interrupt)) void irq14 (const void* ptr);
	//__attribute__((interrupt)) void irq15 (const void* ptr); reserved
}

#endif