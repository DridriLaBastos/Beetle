#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#ifdef DEBUG
    #define BDG ASM ("xchg %bx, %bx")
#else
    #define BDG
#endif

extern "C" void main (void);

#endif