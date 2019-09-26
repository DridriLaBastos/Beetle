#ifndef MULTIBOOT_HPP
#define MULTIBOOT_HPP

#include <stdint.h>

namespace BEETLE {namespace MULTIBOOT {
	struct ModuleInfo
	{
		void* modStart;
		void* modEnd;
		const char* modString;
		uint32_t :32;//Reserved field
	} __attribute__((packed));//I don't really like using this but it permet to use compiler arithmetic to compute addresses

	class MultibootHelper
	{
		public:
			enum FLAGS
			{
				MEM_INFO	= 1 << 0,
				BOOT_DEVICE	= 1 << 1,
				CMD_LINE	= 1 << 2,
				MODULE		= 1 << 3
			};

		public:
			MultibootHelper (const unsigned int multibootInfoDataStructPtr);

			bool isFlagSet (const unsigned int flag) const { return (m_flags & flag) == flag;}
			unsigned int getBootmoduleCount(void) const { return m_multibootInfoStructPtr[5]; }
			ModuleInfo* getNextModuleInfoStruct (void);
			ModuleInfo* getModuleInfoStructForModuleNumber (const unsigned int moduleNumber) const;

		private:
			const uint32_t* m_multibootInfoStructPtr;
			const uint32_t m_flags;
			unsigned int m_currentModuleInfoStruct;
	};
}}

#endif