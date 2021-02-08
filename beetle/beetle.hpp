#ifndef BEETLE_HPP
#define BEETLE_HPP

#include "beetle/mm.hpp"
#include "beetle/process.hpp"
#include "beetle/services.hpp"
#include "beetle/multiboot.hpp"

#define NOP ASM("nop")
#define HLT ASM("hlt")
#define BDG ASM("xchg %bx, %bx")

#endif