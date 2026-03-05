#ifndef BEETLE_CONST_HPP
#define BEETLE_CONST_HPP

namespace BEETLE::CONST {
    /**
     * Beetle API call are made using the interrupt vector 32
     */
    constexpr unsigned int SYSCALL_VECTOR = 32;
}

#endif