#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

/**
 * This file defines all the functions that the kernel requires an arch to implements
 */

#include <stdint.h>

namespace ARCH
{
	/**
	 * \brief First function from the arch called by the kernel
	 * 
	 * \details The role of this function is to initialize the minimum setup running for the architecture. Advanced functionalities of an architecture should not be initialized here
	 */
	void init(void);

	using task_t = uint32_t;

	namespace TASK
	{
		task_t task_createUserLand(const void* entryPoint);
		void task_switch(const task_t t);
	}

	void endlessLoop(void);
}

#endif