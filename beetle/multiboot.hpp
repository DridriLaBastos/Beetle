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
			MultibootHelper (const uint32_t* const multibootInfoPtr);

			bool isFlagSet (const FLAGS flag) const;
			unsigned int getBootmoduleCount(void) const;
			ModuleInfo* getBootModuleInfo (const unsigned int n) const;

		private:
			const uint32_t* m_multibootInfoPtr;
	};
}}

#endif