#include "include/protected.hpp"

using namespace ARCH::I386;

//Those symbols are defined in the assembly file preinit.s
extern "C" uint64_t* gdt;
extern "C" unsigned int gdt_current;

extern "C" uint64_t* idt;
extern "C" unsigned int idt_current;

extern "C" void* gdtr;
extern "C" void* idtr;

//TODO: needs error checking
void IDT::push (const uint64_t descriptor) { idt[idt_current] = descriptor; idt_current += 1; }

void IDT::push (const uint64_t descriptor, const unsigned int n)
{
	idt_current = n;
	push(descriptor);
}

void IDT::load()
{
	asm("cli");
	asm("lidt idtr");
	asm("sti");
}