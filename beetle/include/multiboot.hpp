#ifndef MULTIBOOT_HPP
#define MULTIBOOT_HPP

#include <stdint.h>

namespace BEETLE {namespace MULTIBOOT {
	struct ModuleStruct
	{
		unsigned int* modStart;
		unsigned int* modEnd;
		char* modString;
	};

	class MultibootInfos
	{
		public:
			MultibootInfos (const unsigned int multibootInfoTableStartAddr);

			//TODO: remove constexpr, those functions will never be called at compile time because they need runtime infos
			constexpr bool isFlagSet (const unsigned int flag) const { return (m_flags & flag) == flag;}
			constexpr unsigned int getBootmoduleCount(void) const { return ((uint32_t*)m_multibootInfosTableStartAddr)[5]; }
			constexpr unsigned int getFirstBootModuleAddr (void) const { return ((uint32_t*)m_multibootInfosTableStartAddr)[6]; }

		private:
			const unsigned int m_multibootInfosTableStartAddr;
			const unsigned int m_flags;
	};
}}

#endif