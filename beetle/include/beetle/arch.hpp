#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

/**
 * This file defines all the functions that the kernel requires an arch to implements
 */

namespace ARCH
{
	/**
	 * \brief First function called by the kernel
	 * 
	 * The role of this function is to initialize the minimum setup running for the architecture. Advanced functionnalities of an architecture should not be initialized here
	 */
	void init(void);
	void endlessLoop(void);
}

#endif