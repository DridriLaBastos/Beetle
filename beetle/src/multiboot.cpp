#include "../multiboot.hpp"

BEETLE::MULTIBOOT::MultibootHelper::MultibootHelper(const uint32_t* const multibootInfoPtr): m_multibootInfoPtr(multibootInfoPtr)
{}

bool BEETLE::MULTIBOOT::MultibootHelper::isFlagSet(const FLAGS flag) const
{
	const uint32_t flags = m_multibootInfoPtr[0];
	return flags & flag;
}

unsigned int BEETLE::MULTIBOOT::MultibootHelper::getBootmoduleCount() const
{ return m_multibootInfoPtr[5]; }

BEETLE::MULTIBOOT::ModuleInfo* BEETLE::MULTIBOOT::MultibootHelper::getBootModuleInfo(const unsigned int n) const
{
	const uint32_t bootmoduleCount = getBootmoduleCount();

	if (bootmoduleCount == 0)
		return nullptr;
	
	if (n >= bootmoduleCount)
		return nullptr;
	
	ModuleInfo* moduleInfos = (ModuleInfo*)(m_multibootInfoPtr[6]);
	return &moduleInfos[n];
}