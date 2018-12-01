#include "i386.hpp"

extern "C" 
{
    void __attribute__((fastcall)) load_ds    (const unsigned int ds_descriptor);
    void __attribute__((fastcall)) load_es    (const unsigned int es_descriptor);
    void __attribute__((fastcall)) load_fs    (const unsigned int fs_descriptor);
    void __attribute__((fastcall)) load_gs    (const unsigned int gs_descriptor);
    void __attribute__((fastcall)) load_ss    (const unsigned int ss_descriptor);
}

void CPU::I386::GDT::select(const SEGMENT_NAMES segment_name, const uint16_t segment_pos, const int rpl)
{
    const uint16_t segment_selector = rpl | (segment_pos << 3);

    switch (segment_name)
    {
        case SEGMENT_NAMES::DS:
            load_ds(segment_selector);
            break;
        
        case SEGMENT_NAMES::ES:
            load_es(segment_selector);
            break;
        
        case SEGMENT_NAMES::FS:
            load_fs(segment_selector);
            break;
        
        case SEGMENT_NAMES::GS:
            load_gs(segment_selector);
            break;
        
        case SEGMENT_NAMES::SS:
            load_ss(segment_selector);
            break;
    }
}
