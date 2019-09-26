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
				uint8_t		e_ident[EI_NIDENT];
				Elf32_Half	e_type;
				Elf32_Half	e_machine;
				Elf32_Word	e_version;
				Elf32_Addr	e_entry;
				Elf32_Off	e_phoff;
				Elf32_Off	e_shoff;
				Elf32_Word	e_flags;
				Elf32_Half	e_ehsize;
				Elf32_Half	e_phentsize;
				Elf32_Half	e_phnum;
				Elf32_Half	e_shentsize;
				Elf32_Half	e_shnum;
				Elf32_Half	e_shstrndx;
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
			const uint8_t* m_elfDataBuffer;
			Elf32_Ehdr m_elfHeader;
	};
}

#endif