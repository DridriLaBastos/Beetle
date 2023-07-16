set(CMAKE_SYSTEM_NAME Beetle)
set(CMAKE_SYSTEM_PROCESSOR i386)
set(CMAKE_SYSTEM_VERSION 0.0.1)

if (NOT ${LINUX})
	set(TARGET_GNU_PREFIX "i686-elf-")
endif()
set(CMAKE_C_COMPILER ${TARGET_GNU_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TARGET_GNU_PREFIX}g++)
set(CMAKE_AR ${TARGET_GNU_PREFIX}ar)
set(CMAKE_LINKER ${TARGET_GNU_PREFIX}ld)
set(SIZE_EXEC ${TARGET_GNU_PREFIX}size)

set(CMAKE_C_FLAGS_INIT "-m32 -march=i386 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT}")

# The development compiler installed is not abble to compile a simple program without additional flags (libc start and
# end routines are not provided at this stage). We tell cmake that the compilers are working, when needed, they will be
# tested with the right flags
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

find_program(XORRISO xorriso) # Needed by grub-mkrescue
find_program(GRUB_MKRESCUE grub-mkrescue REQUIRED)
find_program(BOCHS bochs)
find_program(NM ${TARGET_GNU_PREFIX}nm)
find_program(OBJDUMP ${TARGET_GNU_PREFIX}objdump)
