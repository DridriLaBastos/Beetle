#include "beetle/arch.hpp"
#include "beetle/process.hpp"

void BEETLE::Send(const ServiceAddress dest, const Message m)
{
    ARCH::TrapSyscall(BEETLE::ESysCallFn::SEND);
}

BEETLE::Message BEETLE::Receive(const ServiceAddress src)
{
    ARCH::TrapSyscall(BEETLE::ESysCallFn::RECV);
}
