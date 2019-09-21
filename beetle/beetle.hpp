#ifndef BEETLE_HPP
#define BEETLE_HPP

#define ALL

#if defined BEETLE_MM
	#undef ALL
	#include "include/mm.hpp"
#endif

#if defined BEETLE_PM
	#undef ALL
	#include "include/process.hpp"
#endif

#if defined BEETLE_MB
	#undef ALL
	#include "include/multiboot.hpp"
#endif

#if defined ALL
	#include "include/mm.hpp"
	#include "include/process.hpp"
	#include "include/multiboot.hpp"
#endif

#define DEBUG

#define ASM(a) __asm__ volatile (a)

#define NOP ASM("nop")
#define HLT ASM("hlt")
#define BDG ASM("xchg %bx, %bx")

#endif