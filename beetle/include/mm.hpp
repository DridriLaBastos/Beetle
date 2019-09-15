#ifndef MM_HPP
#define MM_HPP

#include <stdint.h>

namespace BEETLE
{
	//Simple memory manager that allocate memory by chunk of 4kb. Each chunks is represented as an integer set to 1
	//if the page is used and non zero otherwise
	//TODO: can be more RAM efficient
	//TODO: modularize this
	class MemoryManager
	{
		public:
			MemoryManager();

			uint8_t* allocate (const unsigned int pageNumber = 1);
			void free (const unsigned pageIndex, const unsigned int pageNumberToFree = 1);

		private:
			uint8_t* m_usedChunksMap;
		
		private:
			const unsigned int m_totalNumberOfPages = 0x10000;
	};
}

#endif