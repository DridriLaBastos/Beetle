cmake_minimum_required(VERSION 3.10)

set(TARGET "i386")

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES CXX ASM_NASM
		)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION $<$<CONFIG:Release>:TRUE>)

set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS s)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)

add_subdirectory(beetle)

add_custom_target(run COMMAND bochs -q
					WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
