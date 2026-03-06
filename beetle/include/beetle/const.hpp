#ifndef BEETLE_CONST_HPP
#define BEETLE_CONST_HPP

namespace BEETLE {
    /**
     * Beetle API calls are made using interrupt vector 32
     */
    constexpr unsigned int SYSCALL_VECTOR = 32;

    enum class ESysCallFn : unsigned int
    {
        SEND = 0,
        RECV = 1,
    };
}

#endif