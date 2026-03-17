#include <beetle/arch.hpp>

static void RecvSyscall()
{

}

static void SendSyscall()
{
    
}

void BEETLE::API::Syscall(const BEETLE::ESysCallFn syscallFn)
{
    switch (syscallFn)
    {
        case ESysCallFn::RECV:
            RecvSyscall();
        
        case ESysCallFn::SEND:
            SendSyscall();
    }
}