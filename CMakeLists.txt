cmake_minimum_required(VERSION 3.12 FATAL_ERROR) #3.12 needed to use file GLOB CONFIGURE_DEPENDS option

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES C CXX ASM_NASM
		)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

set(BEETLE_TARGET "" CACHE STRING "The target cpu architecture for which Beetle will be compiled")
set(BEETLE_PLATFORM "" CACHE STRING "The target platform for which Beetle will be compiled")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE true)

# include_directories("${CMAKE_SOURCE_DIR}")
# include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/libc")

# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sysroot)

# set(MISC_OBJ_FILES
# 	${PROJECT_BINARY_DIR}/libc/misc/crt0.o
# 	${PROJECT_BINARY_DIR}/libc/misc/crti.o
# 	${PROJECT_BINARY_DIR}/libc/misc/crtn.o
# )

# add_subdirectory(libc)
# add_subdirectory(services)

add_subdirectory(beetle)

