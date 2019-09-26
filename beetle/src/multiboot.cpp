#include "../multiboot.hpp"

BEETLE::MULTIBOOT::MultibootHelper::MultibootHelper(const unsigned int multibootInfoStructPtr): m_multibootInfoStructPtr((uint32_t*)multibootInfoStructPtr), m_flags(m_multibootInfoStructPtr[0]), m_currentModuleInfoStruct(0)
{}

BEETLE::MULTIBOOT::ModuleInfo* BEETLE::MULTIBOOT::MultibootHelper::getNextModuleInfoStruct()
{
	const uint32_t totalModuleLoadedCount = getBootmoduleCount();

	if (totalModuleLoadedCount == 0)
		return nullptr;
	
	if (m_currentModuleInfoStruct == totalModuleLoadedCount)
		return nullptr;
	
	ModuleInfo* ret = (ModuleInfo*)(m_multibootInfoStructPtr[6]);
	return &(ret[m_currentModuleInfoStruct++]);
}

BEETLE::MULTIBOOT::ModuleInfo* BEETLE::MULTIBOOT::MultibootHelper::getModuleInfoStructForModuleNumber(const unsigned int moduleNumber) const
{
	const uint32_t totalModuleLoadedCount = getBootmoduleCount();

	if (totalModuleLoadedCount == 0)
		return nullptr;

	const unsigned int safeModuleNumber = moduleNumber % totalModuleLoadedCount;
	ModuleInfo* ret = (ModuleInfo*)(m_multibootInfoStructPtr[6]);
	return &(ret[safeModuleNumber]);
}