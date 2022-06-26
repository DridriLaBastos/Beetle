project(ARCH)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB ASM_NASM_SOURCES CONFIGURE_DEPENDS "*.s")

foreach(asm_file ${ASM_NASM_SOURCES})
	set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM_NASM)
endforeach(asm_file ${ASM_NASM_SOURCES})

set_source_files_properties(interrupts.cpp PROPERTIES COMPILE_FLAGS "-mgeneral-regs-only -mno-red-zone")

add_library(${TARGET} STATIC ${CXX_SOURCES} ${ASM_NASM_SOURCES})

target_include_directories(${TARGET} PRIVATE include)
