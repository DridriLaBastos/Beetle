project(Architecture)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${BEETLE_TARGET})
	message(FATAL_ERROR "A folder named ${BEETLE_TARGET} must exist inside beetle/arch for the kernel to be compiled for the target ${BEETLE_TARGET}. It must contains a cmake objects library called ${BEETLE_TARGET} that implements the target specific functions declared in the file include/beetle/arch.hpp for the specified ${BEETLE_TARGET} target, the _start function that will put the system in a correct state and call the kmain function, a linker script that contains the instruction to create an elf for the target architecture")
endif()

configure_file(${BEETLE_TARGET}/types.inl ${PROJECT_SOURCE_DIR}/include/arch/types.inl)

add_compile_definitions(ARCH_IMPL)
add_subdirectory(${BEETLE_TARGET})

add_library(arch STATIC $<TARGET_OBJECTS:${BEETLE_TARGET}>)
target_include_directories(arch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
