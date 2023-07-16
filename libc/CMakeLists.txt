project("Beetle libC")

file(GLOB LIBC_C_SRC CONFIGURE_DEPENDS src/*.c src/i386/*.c src/i386/*.asm)
file(GLOB LIB_C_HDR *.h)

message( "nasm extension : ${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS} asm extension : ${CMAKE_ASM_SOURCE_FILE_EXTENSIONS}" )

add_library(c STATIC ${LIBC_C_SRC} ${ARCH_ASM_SRC} ${LIB_C_HDR})
add_library(kernelc STATIC ${LIBC_C_SRC} ${ARCH_ASM_SRC} ${LIB_C_HDR})

target_compile_options(kernelc PRIVATE -ffreestanding -fno-stack-protector)
