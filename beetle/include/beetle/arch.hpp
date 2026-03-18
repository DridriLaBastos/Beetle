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
	 * \brief Must initialize the architecture and connect the kernel API
	 * 
	 * This function is called at the very begin of the initialization of the kernel. It is free to initialize
	 * the architecture as it want but need to provides a usable environment from the kernel.
	 * 
	 * It also has the job of linking the kernel API function declared in the namespace BEETLE::API to the arch
	 * layer. Those function will be implemented by the kernel in the src/api folder. This function must use
	 * the configuration variable inside beetle/config.hpp to configure the different part of the hardware. More
	 * informations of what the kernel requires for its api is available in the BEETLE::API namespace documentation
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
	 * This function is called after the kernel initialized it self to be able to handle the arch events. In particular
	 * the function should inhibit the main timer and enable the tick function registered to be called
	 * (see @ref ConfigureTick).
	 * 
	 * This function do the opposite of @ref ARCH::Isolate()
	 * 
	 */
	void Connect(void);

	/**
	 * @brief Make a way for the early kernel stage to tell something
	 * 
	 * This function might be called in the early initialization stage. When no FS driver have been loaded and
	 * there is no stdin, stdout and stderr, this function will be called as a debug tool. The arch layer is required
	 * to implemented this function. Usually it will output data in polled mode to a serial port to be defined by
	 * the arch layer but the kernel does not force anything. It is an early stage bypass, the output destination
	 * is at the discretion of the architecture implementation.
	 */
	int DebugOutput(const char* fmt, ...) __attribute__((format(printf,1,2)));

	//TODO: redo the doc
	/**
	 * @brief Configure the hardware tick interrupt handler
	 * 
	 * This function must configure the main timer of the architecture layer to call the supplied handler
	 * at the tick interval required. At the end of this function the main timer of architecture must be 
	 * ready to be enabled but should not be enable.
	 * 
	 * @param minUSec 	This is the minimum time in micro seconds the kernel requires between 2 ticks.
	 * 					The time can be greater or lower depending on hardware capabilities. Even if its not
	 * 					harmful the arch layer should try to be as close as possible of the given data. Since
	 * 					The time tick is configurable the user could choose a higher time tick to enhance 
	 * 					energy efficiency or lower for greater responsiveness.
	 */
	void ConfigureTick(const unsigned int minUSec);

	void MakeSyscall (const BEETLE::ESysCallFn syscallFn);
}

/**
 * In this namespace the function definition for Beetle API is provided. By having the function definition here
 * the architecture layer can use the symbols instead of having to rely on a function pointers. If it add a bit
 * of decoupling since now the kernel is not fully responsible of giving function to the architecture side, it
 * permits to use function call instead of pointer to function call in the architecture layer. Since everything
 * is statically linked in the final executable it will permit inlining this function call and improving
 * performances.
 * 
 * The kernel is responsible for the implementation of those functions
 */
namespace BEETLE::API
{
	void Schedule (void);

	void Syscall (const BEETLE::ESysCallFn syscallfn);
	
}

#endif