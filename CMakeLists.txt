cmake_minimum_required(VERSION 3.12 FATAL_ERROR) #3.12 needed to use file GLOB CONFIGURE_DEPENDS option

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES C CXX ASM_NASM
		)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

set(TARGET "i386")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE true)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/libc")

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sysroot)

set(MISC_OBJ_FILES
	${PROJECT_BINARY_DIR}/libc/misc/crt0.o
	${PROJECT_BINARY_DIR}/libc/misc/crti.o
	${PROJECT_BINARY_DIR}/libc/misc/crtn.o
)

add_subdirectory(libc)
add_subdirectory(services)

set(PMN_BINARY_PATH $<TARGET_FILE:pmn.elf> CACHE PATH "Path to the elf of the process management program")

add_subdirectory(beetle)

