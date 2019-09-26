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
			//TODO: add a way to free the memory even if the processus that created it didn't
			struct MemoryBlockInfo
			{
				MemoryBlockInfo* previous;	//When previous = nullptr, this the first allocated block
				MemoryBlockInfo* next;		//When next = nullptr, this is the last allocated block
				unsigned long size;			//Size of the allocated block
			};

		public:
			MemoryManager();

			uint8_t* allocate (const unsigned int byteNumberToAllocate);
			void free (const uint8_t* HeapAllocatedPtr);
		
		private:
			MemoryBlockInfo* m_firstMemoryBlockPtr;
	};
}

#endif