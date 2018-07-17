/**
 *          COURNAND Adrien - 3/06/1996
 *              GNU GPL v3.0
 * 
 */

#ifndef __I386_HPP__
#define __I386_HPP__

#include <stdint.h> //provided by gcc

//Possible values for the field P of any descriptors
constexpr unsigned int PRESENT = 1 << 3;
constexpr unsigned int NO_PRESENT = 0;

//Possible values for the field S in segment descriptor
constexpr unsigned int SYSTEM = 0;
constexpr unsigned int CODE_DATA = 1;

//Possible values for the field DPL in any descriptors
constexpr unsigned int PRIVILEGE0 = 0;
constexpr unsigned int PRIVILEGE1 = 1 << 1;
constexpr unsigned int PRIVILEGE2 = 2 << 1;
constexpr unsigned int PRIVILEGE3 = 3 << 1;

extern "C" 
{
    void __attribute__((fastcall)) switch_idt (const unsigned int idtr_addr);
    void __attribute__((fastcall)) switch_gdt (const unsigned int gdtr_addr);
}

/**
 * In this namespace any i386 architecture feature will be implemented
 * */
namespace CPU::I386
{
    using descriptor_t = uint64_t;

    struct Register
    {
        uint16_t limit;
        uint32_t base;
    }__attribute__((packed));

    struct SegmentDescriptor
    {
        uint16_t segment_limit_1;
        uint16_t base_address_1;
        uint8_t  base_address_2;
        uint8_t  type:4;
        uint8_t  access:4;
        uint8_t  segment_limit_2:4;
        uint8_t  other:4;
        uint8_t  base_address_3;
    }__attribute__((packed));

    struct I_TGateDescriptor
    {
        uint16_t offset_1;
        uint16_t segment_selector;
        uint16_t :5, it:7, access:4;//First 5 bits are reserved and it = 0x70 for interrupt gate and 0x78 for trap gate
                                    //The D field (bit 11) is always set to 1 for 32bits trap/interrupt gate
        uint16_t offset_2;
    }__attribute__((packed));

    struct TaskGateDescriptor
    {
        uint16_t :16;
        uint16_t tss_segment_selector;
        uint16_t :8, tss_value:5, access:3;
        uint16_t :16;
    }__attribute__((packed));

    enum CODE_DATA_SEGMENT_T
    {
        D_RO = 0,//Data read only
        D_ROA,   //Data read only accessed
        D_RW,    //Data read/write
        D_RWA,   //Data read/write accessed
        D_ROE,   //Data read only expand down
        D_ROEA,  //Data read only expand down accessed
        D_RWE,   //Data read write expand down
        D_RWEA,  //Data read write expand down accessed

        C_EO,    //Code execute only
        C_EOA,   //Code execute only accessed
        C_ER,    //Code execute read
        C_ERA,   //Code execute read accessed
        C_EOC,   //Code execute only conforming
        C_EOCA,  //Code execute only confirming accessed
        C_ERC,   //Code execute read conforming
        C_ERCA   //Code execute read conforming accessed
    };

    enum SYSTEM_SEGMENT_T
    {
        // 0 = reserved
        TSS_A_16 = 1, //16 bits TSS available
        LDT,          //LDT
        TSS_B_16,     //16 bits TSS busy
        CG_16,        //16 bits call gate
        TG,           //task gate
        IG_16,        //16 bits interrupt gate
        TG_16,        //16 bits trap gate
        // 8 = reserved
        TSS_A_32 = 9, //32 bits TSS available
        // 10 = reserved
        TSS_B_32 = 11, //32 bits TSS busy
        CG_32,         //32 bits call gate
        // 13 = reserved
        IG_32 = 14,    //32 bits interrupt gate
        TG_32          //32 bits trap gate
    };

    enum class SEGMENT_NAMES
    {
        DS, ES, FS, GS, SS /* There is no CS because cs can't be selected using a move instruction */
    };

    inline SegmentDescriptor create_segment_descriptor(const uint32_t base, const uint32_t limit, const int type, const int access, const int other)
    {
        //Explicite conversion to silent some warnigs
        return {(uint16_t)(limit & 0xFFFF), (uint16_t)(base & 0xFFFF), (uint8_t)((base & 0xFF0000) >> 16), (uint8_t)type, (uint8_t)access, (uint8_t)((limit & 0xF0000) >> 16), (uint8_t)other, (uint8_t)((base & 0xFF000000) >> 24)};
    }

    inline I_TGateDescriptor create_interruptgate_descriptor (const uint32_t offset, const uint16_t segment_selector, const int access)
    {
        //Explicite conversion to silent some warnings
        return {(uint16_t)(offset & 0xFFFF), segment_selector, (uint16_t)0x70, (uint16_t)access, (uint16_t)(offset  >> 16)};
    }

    inline I_TGateDescriptor create_trapgate_descriptor (const uint32_t offset, const uint16_t segment_selector, const int access)
    {
        //Explicite conversion to silent some warnings
        return {(uint16_t)(offset & 0xFFFF), segment_selector, (uint16_t)0x78, (uint16_t)access, (uint16_t)((offset & 0xFFFF0000) >> 16)};
    }

    /*inline TaskGateDescriptor create_taskgate_descriptor (const uint16_t tss_segment_selector, const int access)
    {
        TaskGateDescriptor ret;
        ret.tss_segment_selector = tss_segment_selector;
        ret.tss_value = 0b00101;
        ret.access = access;

        return ret;
    }*/

    class Table
    {
        public:
            Table(const uint16_t count, const uint32_t base);

            void add (const SegmentDescriptor descriptor);
            void add (const I_TGateDescriptor descriptor);

            virtual void add (const descriptor_t descriptor);
            virtual void del (void);
            virtual void update (const uint16_t pos, const descriptor_t new_descriptor);
            virtual void makeCurrent (void) const = 0;
        
        protected:
            Register m_reg;
            uint16_t m_count;
    };

    class LDT: public Table
    {

    };

    class GlobalTable: public Table
    {
        public:
            enum class TYPE
            {
                GDT, IDT
            };

        public:
            GlobalTable(const uint16_t count, const uint32_t base);
            GlobalTable(const GlobalTable&) = delete;//No copy constructor for GlobalTable
            static void retrieve (const TYPE type, GlobalTable& dest);
    };

    class GDT: public GlobalTable
    {
        public:
            GDT(void);
        
        public:
            void select (const SEGMENT_NAMES segment_name, const uint16_t segment_selector, const int rpl);
            void del () override;
            inline void makeCurrent (void) const final { switch_gdt((int)&m_reg); }
    };

    class IDT: public GlobalTable
    {
        public:
            IDT(void): GlobalTable(32, 0) { }

            inline void makeCurrent(void) const final { switch_idt((int)&m_reg); }
    };
}
#endif