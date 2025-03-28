project(ARCH LANGUAGES ASM_NASM)

set_source_files_properties(src/interrupts.cpp PROPERTIES COMPILE_FLAGS "-mgeneral-regs-only -mno-red-zone")

add_library(${BEETLE_TARGET} OBJECT src/preinit.asm src/i386.cpp)

target_link_libraries(${BEETLE_TARGET} PRIVATE kc ksys)
