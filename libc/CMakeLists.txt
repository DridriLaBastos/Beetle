project("Beetle libC")

file(GLOB LIBC_C_SRC CONFIGURE_DEPENDS src/*.c src/i386/*.c src/i386/*.asm)
file(GLOB LIB_C_HDR *.h)

message( "nasm extension : ${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS} asm extension : ${CMAKE_ASM_SOURCE_FILE_EXTENSIONS}" )

add_library(c STATIC ${LIBC_C_SRC} ${ARCH_ASM_SRC} ${LIB_C_HDR})
add_library(kernelc STATIC ${LIBC_C_SRC} ${ARCH_ASM_SRC} ${LIB_C_HDR})
add_library(misc OBJECT src/misc/crt0.c src/misc/crti.asm src/misc/crtn.asm)

add_dependencies(c misc)

# Remaking a sysroot
# On my developments machine, some version of gcc asks for a libc.a or a libg.a. Both version should be a c library
add_custom_command(TARGET c POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E echo "* * * MAKING SYSROOT * * *"
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crt0.c.obj ${CMAKE_SYSROOT_USR_LIB}/crt0.o
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crti.asm.obj ${CMAKE_SYSROOT_USR_LIB}/crti.o
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crtn.asm.obj ${CMAKE_SYSROOT_USR_LIB}/crtn.o
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${CMAKE_SYSROOT_USR_LIB}/libc.a
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${CMAKE_SYSROOT_USR_LIB}/libg.a
)

target_compile_options(kernelc PRIVATE -ffreestanding -fno-stack-protector)
