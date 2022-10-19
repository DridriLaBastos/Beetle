#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

/**
 * This file defines all the functions that the kernel requires an arch to implements
 */

#include "../../../libc/stdint.h"

namespace ARCH
{
	/**
	 * \brief First function from the arch called by the kernel
	 * 
	 * \details The role of this function is to initialize the minimum setup running for the architecture. Advanced functionalities of an architecture should not be initialized here
	 */
	void init(void);
	void endlessLoop(void);
	void moveToUserLand(const uintptr_t linearAddress);
}

#endif