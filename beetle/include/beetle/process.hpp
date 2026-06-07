#ifndef BEETLE_PROCESS_HPP
#define BEETLE_PROCESS_HPP

#include <stdint.h>
#include "beetle/arch.hpp"

namespace BEETLE
{
    using Message = uint32_t;
    using ServiceAddress = uint32_t;

    constexpr ServiceAddress ANY = 0;

    void Send(const ServiceAddress dest, const Message m);
    Message Receive(const ServiceAddress src);

    struct Process
    {
        ARCH::ExecutionContext context;
        Process* next;
    };

    static Process initProcess;
}

#endif