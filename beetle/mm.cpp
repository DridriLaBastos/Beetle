#include "include/mm.hpp"

//TODO: implement this properly
void memcpy (const uint8_t* const src, uint8_t* const dest, const unsigned int count)
{
	for (unsigned int i = 0; i < count; ++i)
		dest[i] = src[i];
}

namespace BEETLE
{	
	MemoryManager::MemoryManager(): m_firstMemoryBlockPtr(nullptr)
	{
	}

	//TODO: make sure that the initial memory that used is being marked as used
	uint8_t* MemoryManager::allocate(const unsigned int byteNumberToAllocate)
	{
		//It is assumed that the boot stage 1 program will be less than 1 MB. The boot stage 1 program is loaded at 1MB
		//so the memory manager start allocating memory at 1MB + 1MB = 2Mb
		MemoryBlockInfo* createdMemoryBlockPtr = (MemoryBlockInfo*)(2*1024*1024);

		//If m_firstMemoryBlockPtr == nullptr, then no memory has been allocated yet and it is possible to directly allocate a block
		//in place at 2MB
		if (m_firstMemoryBlockPtr == nullptr)
		{
			createdMemoryBlockPtr->next = nullptr;
			createdMemoryBlockPtr->previous = nullptr;
			createdMemoryBlockPtr->size = byteNumberToAllocate;

			m_firstMemoryBlockPtr = createdMemoryBlockPtr;
		}
		else
		{
			//TODO: handle end of memory
			//If memory has been allocated the function goes throw all the block to search for either:
			// * a space between two blocks were asked memory can be puts
			// * the block the last allocated block (the block which has the next pointer to null)
			MemoryBlockInfo* currentMemoryBlockInfo = m_firstMemoryBlockPtr;

			while (currentMemoryBlockInfo->next != nullptr)
			{
				const unsigned long addrOfLastByteOfCurrentMemoryBlock = (unsigned long)currentMemoryBlockInfo + sizeof(MemoryBlockInfo) + currentMemoryBlockInfo->size;
				if ((unsigned long)currentMemoryBlockInfo->next - addrOfLastByteOfCurrentMemoryBlock > byteNumberToAllocate)
					break;
				
				currentMemoryBlockInfo = currentMemoryBlockInfo->next;
			}

			//When a space in RAM is found, it is used and the doubly linked list is updated
			createdMemoryBlockPtr = currentMemoryBlockInfo + sizeof(MemoryBlockInfo) + currentMemoryBlockInfo->size;
			createdMemoryBlockPtr->next = currentMemoryBlockInfo->next;
			createdMemoryBlockPtr->previous = currentMemoryBlockInfo;

			currentMemoryBlockInfo->next->previous = currentMemoryBlockInfo;

			createdMemoryBlockPtr->size = byteNumberToAllocate;
		}

		return (uint8_t*)(createdMemoryBlockPtr + sizeof(MemoryBlockInfo));
	}

	//TODO: check if the pointer being used was allocated or not
	void MemoryManager::free(const uint8_t* const heapAllocatedPtr)
	{
		MemoryBlockInfo* currentMemoryBlockInfo = (MemoryBlockInfo*)(heapAllocatedPtr - sizeof(MemoryBlockInfo));

		if (currentMemoryBlockInfo->previous != nullptr)
			currentMemoryBlockInfo->previous->next = currentMemoryBlockInfo->next;
		else
			m_firstMemoryBlockPtr = currentMemoryBlockInfo->next;
		
		if (currentMemoryBlockInfo->next != nullptr)
			currentMemoryBlockInfo->next->previous = currentMemoryBlockInfo->previous;
	}
}