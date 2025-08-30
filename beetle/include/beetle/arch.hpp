#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

namespace ARCH
{
	/**
	 * \brief First function from the arch called by the kernel
	 *
	 * \details The role of this function is to initialize the minimum setup running for the architecture. Advanced functionalities of an architecture should not be initialized here
	 */
	void Init(void *firstAvailableMemory);
	void EndlessLoop(void);
	void MoveToUserLand(void *execFileBaseAddress, void *linearAddress);
}

#endif