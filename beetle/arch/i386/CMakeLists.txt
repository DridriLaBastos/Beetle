project(ARCH LANGUAGES ASM_NASM)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB ASM_SOURCES CONFIGURE_DEPENDS "src/*.asm")

set_source_files_properties(src/interrupts.cpp PROPERTIES COMPILE_FLAGS "-mgeneral-regs-only -mno-red-zone")

add_library(${BEETLE_TARGET} OBJECT ${CXX_SOURCES} ${ASM_SOURCES})

target_include_directories(${BEETLE_TARGET} PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(${BEETLE_TARGET} PRIVATE kc)
