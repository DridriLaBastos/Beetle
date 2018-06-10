#include "i386.hpp"

CPU::I386::Table::Table(const uint16_t count, const uint32_t base): m_count(0)
{
    m_reg = {(uint16_t)(8 * count - 1), base};

    for (uint16_t i = 0; i < count; ++i)
    {
        ((uint64_t*)m_reg.base)[i] = 0;
    }
}

void CPU::I386::Table::add(const SegmentDescriptor descriptor) 
{
    void* tmp = (void*)&descriptor;
    add(*((descriptor_t*)tmp));
}

void CPU::I386::Table::add(const I_TGateDescriptor descriptor)
{
    void* tmp = (void*)&descriptor;
    add(*((descriptor_t*)tmp));
}

void CPU::I386::Table::add(const descriptor_t descriptor)
{
    descriptor_t* table = (descriptor_t*)m_reg.base;
    table[m_count++] = descriptor;
}

void CPU::I386::Table::del()
{
    (m_count > 0) ? m_count-- : m_count;
}

void CPU::I386::Table::update(const uint16_t pos, const descriptor_t new_descriptor)
{
    descriptor_t* table = (descriptor_t*)m_reg.base;
    table[pos] = new_descriptor;
}