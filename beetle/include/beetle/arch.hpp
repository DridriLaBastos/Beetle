#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

/**
 * This file defines all the functions that the kernel requires an arch to implements
 */

namespace ARCH
{
	void init(void);
	void endlessLoop(void);
}

#endif