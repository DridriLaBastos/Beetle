project(ARCH LANGUAGES C CXX ASM_NASM)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB ASM_NASM_SOURCES CONFIGURE_DEPENDS "src/*.s")

foreach(asm_file ${ASM_NASM_SOURCES})
	set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM_NASM)
endforeach(asm_file ${ASM_NASM_SOURCES})

set_source_files_properties(src/interrupts.cpp PROPERTIES COMPILE_FLAGS "-mgeneral-regs-only -mno-red-zone")

add_library(${TARGET} STATIC ${CXX_SOURCES} ${ASM_NASM_SOURCES})

target_include_directories(${TARGET} PRIVATE ${PROJECT_SOURCE_DIR})
