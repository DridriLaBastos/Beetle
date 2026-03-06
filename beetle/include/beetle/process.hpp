#ifndef BEETLE_PROCESS_HPP
#define BEETLE_PROCESS_HPP

#include <stdint.h>

namespace BEETLE
{
    using Message = uint32_t;
    using ServiceAddress = uint32_t;

    constexpr ServiceAddress ANY = 0;

    void Send(const ServiceAddress dest, const Message m);
    Message Receive(const ServiceAddress src);
}

#endif