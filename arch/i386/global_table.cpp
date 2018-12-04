#include "i386.hpp"

extern "C" void __attribute__((fastcall)) get_gdtr   (const int register_adr);
extern "C" void __attribute__((fastcall)) get_idtr   (const int register_adr);

void CPU::I386::GlobalTable::retrieve(const TYPE type, GlobalTable& dest)
{
    (type == TYPE::GDT) ? get_gdtr((int)&dest.m_reg) : get_idtr((int)&dest.m_reg);

    const uint32_t max = (dest.m_reg.limit + 1)/8;

    /*
     * the loop while stop when it find an entry filed with 0's.
     * But for GDTs the first entry is alway 0 the count starts at 1
     */
    uint16_t count = (type == TYPE::GDT) ? 1 : 0;
    uint64_t* table = (uint64_t*)dest.m_reg.base;//descriptors are 64bits long

    while ((count < max) && table[count] != 0){++count;}

    dest.m_count = count;
}