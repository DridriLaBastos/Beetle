#ifndef __I386_INTERRUPTS_HPP__
#define __I386_INTERRUPTS_HPP__

namespace ARCH::I386
{
	__attribute__((interrupt)) void interruptDE (const void* ptr);
	__attribute__((interrupt)) void interruptDB (const void* ptr);
	__attribute__((interrupt)) void interruptNMI (const void* ptr);
	__attribute__((interrupt)) void interruptBP (const void* ptr);
	__attribute__((interrupt)) void interruptOF (const void* ptr);
	__attribute__((interrupt)) void interruptBR (const void* ptr);
	__attribute__((interrupt)) void interruptUD (const void* ptr);
	__attribute__((interrupt)) void interruptNM (const void* ptr);
	__attribute__((interrupt)) void interruptDF (const void* ptr);
	__attribute__((interrupt)) void interruptCS (const void* ptr);
	__attribute__((interrupt)) void interruptTS (const void* ptr);
	__attribute__((interrupt)) void interruptNP (const void* ptr);
	__attribute__((interrupt)) void interruptSS (const void* ptr);
	__attribute__((interrupt)) void interruptGP (const void* ptr);
	__attribute__((interrupt)) void interruptPF (const void* ptr);
	__attribute__((interrupt)) void interruptMF (const void* ptr);
	__attribute__((interrupt)) void interruptAC (const void* ptr);
	__attribute__((interrupt)) void interruptMC (const void* ptr);
	__attribute__((interrupt)) void interruptXM (const void* ptr);
	__attribute__((interrupt)) void interruptVE (const void* ptr);
}

#endif