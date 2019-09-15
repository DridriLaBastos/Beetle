#include "include/mm.hpp"

namespace BEETLE
{
	MemoryManager::MemoryManager()
	{	
		//TODO: store this in kernel space
		//The last Mb is used to store the map
		m_usedChunksMap = (uint8_t*)((unsigned)-1 - 0x10000);
		
		for (int i = 0; i < 256; ++i)
		{
			m_usedChunksMap[i]			= 0xFF;
			m_usedChunksMap[0xFFFF-i]	= 0xFF;
		}

		//The kernel is loaded at 1M, so the 256th pages is used by us
		m_usedChunksMap[256] = 0xFF;
	}

	//TODO: handle the case where there is not enougth RAM free
	uint8_t* MemoryManager::allocate(const unsigned int pageNumber)
	{
		bool spaceAvailable = false;
		unsigned int pageNumberAllocated = 0;

		for (unsigned int i = 0; i < m_totalNumberOfPages; ++i)
		{
			if (m_usedChunksMap[i] == 0)
			{
				bool allocated = true;
				for (unsigned int j = 0; j < pageNumber; ++j)
				{
					if (m_usedChunksMap[i+j] != 0)
					{
						i += j+1;
						break;
						allocated = false;
					}
				}
				
				if (allocated)
				{
					pageNumberAllocated = i;
					
					for (unsigned int j = 0; j < pageNumber; ++j)
						m_usedChunksMap[i+j] = 0xFF;
				}
			}
		}
		return (uint8_t*)(pageNumberAllocated * 4096);
	}

	void MemoryManager::free(const unsigned int pageIndex, const unsigned int pageNumberToFree)
	{
		for (unsigned int i = 0; i < pageNumberToFree; ++i)
			m_usedChunksMap[i] = 0;
	}
}