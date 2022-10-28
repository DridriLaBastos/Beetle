cmake_minimum_required(VERSION 3.12 FATAL_ERROR) #3.12 needed to use file GLOB CONFIGURE_DEPENDS option

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES CXX ASM_NASM
		)

set(CMAKE_CXX_STANDARD 14)

set(TARGET "i386")

set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS s)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
#TODO: Enable plugin when compile gnu binutils
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE true)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")

include_directories("${CMAKE_SOURCE_DIR}")
include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/libc")

add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-march=i386>)

add_subdirectory(beetle)
add_subdirectory(libc)
