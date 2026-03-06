#ifndef __ARCH_SERVICES__
#define __ARCH_SERVICES__

#include "beetle/const.hpp"

/**
 * @file arch.hpp
 * 
 * This file contains the definitions of the functions the kernel requires the arch layer to implement
 * and the documentation of what they must do.
 * 
 */

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

	/**
	 * @brief Isolate the kernel during the early initialization stage so that it is not interrupted during its configuration
	 * 
	 */
	void Isolate(void);

	/**
	 * @brief Reconnect the kernel to the arch.
	 * 
	 * This function is called after the kernel initialized it self to be able to handle the arch events.
	 * This function do the opposite of @ref ARCH::Isolate()
	 * 
	 */
	void Connect(void);

	/**
	 * @brief Register a handle for the provided vector
	 * 
	 * @param vector ISR number
	 * @param handler handler addr to be called
	 */
	void RegisterInterrupt(const unsigned int vector, void(*handler)(void));

	/**
	 * @brief Let the architecture layer populate the CPU and make a trap call into the kernel code to execute the syscall
	 * 
	 */
	//TODO: Reflexion: It might be possible to template this so that the int parameter can be use as an immediate
	// int value 
	void TrapSyscall(const BEETLE::ESysCallFn syscallfn);
}

#endif