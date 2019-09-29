#ifndef ELF_HPP
#define ELF_HPP

#include <stdint.h>

constexpr unsigned int EI_NIDENT = 16;

namespace BEETLE
{
	//TODO: ELF64 Helper
	//Type and structures get from the elf documentation at https://docs.oracle.com/cd/E23824_01/html/819-0690/chapter6-46512.html#scrolltoc
	class ELFHelper
	{
		public:
			using Elf32_Addr	= uint32_t;
			using Elf32_Half	= uint16_t;
			using Elf32_Off		= uint32_t;
			using Elf32_Sword	= int32_t;
			using Elf32_Word	= uint32_t;
		
		public:
			struct Elf32_Ehdr
			{
				uint8_t		e_ident[EI_NIDENT];	//Initial bytes
				Elf32_Half	e_type;			//Identifies the object type
				Elf32_Half	e_machine;		//Specifies the required architecture
				Elf32_Word	e_version;		//Identifies the object file version
				Elf32_Addr	e_entry;		//The virtual address to which the system first transfers control
				Elf32_Off	e_phoff;		//The program header table's file offset in bytes
				Elf32_Off	e_shoff;		//The section header table's file offset in bytes
				Elf32_Word	e_flags;		//Processor specific flags
				Elf32_Half	e_ehsize;		//The elf header's size in btyes
				Elf32_Half	e_phentsize;	//The size in bytes of one entry in the file's program header table
				Elf32_Half	e_phnum;		//The number of entries in the in the program header table
				Elf32_Half	e_shentsize;	//A section header's size in bytes
				Elf32_Half	e_shnum;		//The number of entries in the section header table
				Elf32_Half	e_shstrndx;		//The section header table index of entry that is associated with the section name string table
			};

		public:
			enum class E_TYPE_VALUE
			{
				ET_NONE	= 0,//No file type
				ET_REL,		//Relocatable file
				ET_EXEC,	//Executable file
				ET_DYN,		//Shared object file
				ET_CORE,	//Core file
				ET_LOPROC = 0xFF00, ET_HIPROC = 0xFFFF//Processor specific
			};

			enum class E_MACHINE_VALUE
			{
				EM_NONE		=  0,	//No machine
				EM_SPARC	=  2,	//SPARC
				EM_386		=  3,	//Intel 80386
				EM_SPARC32PLUS = 18,//Sun SPARC 32+
				EM_SPARCV9	= 43,	//SPARC V9
				EM_AMD64	= 62,	//AMD 64
			};

			enum class E_VERSION_VALUE
			{ EV_NONE = 0 };

			enum class E_FLAGS_VALUE
			{
				//0 for x86
			};

			enum class E_IDENT_VALUE
			{
				EI_MAG0 = 0, EI_MAG1, EI_MAG2, EI_MAG3,//File identification
				EI_CLASS,	//File class
				EI_DATA,	//Data encoding
				EI_VERSION,	//File version
				EI_OSABI,	//Operating system/ABI identification
				EI_ABI_VERSION,//ABI version
				EI_PAD,		//Start of padding bytes
			};

			enum class EI_MAG_VALUE
			{
				ELFMAG0 = 0x7F,	//at e_ident[EI_MAG0]
				ELFMAG1 = 'E',	//at e_ident[EI_MAG1]
				ELFMAG2 = 'L',	//at e_ident[EI_MAG2]
				ELFMAG3 = 'F'	//at e_ident[EI_MAG3]
			};

			enum class EI_CLASS_VALUE
			{
				ELFCLASSNONE = 0,	//Invalid class
				ELFCLASS32,			//32-bit objects
				ELFCLASS64,			//64-bit objects
			};

		public:
			ELFHelper (const uint8_t* const elfDataBuffer);
			void setElfDataBuffer(const uint8_t* const newElfDataBuffer);
		
		private:
			void reinitElfHeader(void);
			
		private:
			const uint8_t* m_elfDataBuffer;
			Elf32_Ehdr m_elfHeader;
	};
}

#endif