if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BEETLE_TARGET})
	message(FATAL_ERROR "A folder named ${BEETLE_TARGET} must exist inside beetle/arch for the kernel to be compiled for the target ${BEETLE_TARGET}. It must contains a cmake objects library called ${BEETLE_TARGET} that implements the target specific functions declared in the file include/beetle/arch.hpp for the specified ${BEETLE_TARGET} target, the _start function that will put the system in a correct state and call the kmain function, a linker script that contains the instruction to create an elf for the target architecture")
endif()

add_subdirectory(${BEETLE_TARGET})
