cmake_minimum_required(VERSION 3.10)

set(TARGET "i386")

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES CXX ASM_NASM
		)

set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS s)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
#TODO: Enable plugin when compile gnu binutils
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE true)
set(CMAKE_CXX_FLAGS_RELEASE" ${CMAKE_CXX_FLAGS_RELEASE} -flto")

include_directories(SYSTEM libc/include)
link_directories(${CMAKE_BINARY_DIR}/libc)

add_subdirectory(beetle)
add_subdirectory(libc)

add_custom_target(run COMMAND bochs -q
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
					DEPENDS beetle.elf)
