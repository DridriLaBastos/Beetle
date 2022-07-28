set(CMAKE_SYSTEM_NAME Beetle)
set(CMAKE_SYSTEM_PROCESSOR i386)
set(CMAKE_SYSTEM_VERSION 0.0.1)

set(TARGET_GNU_PREFIX "i686-elf-")
set(CMAKE_C_COMPILER ${TARGET_GNU_PREFIX}gcc -ffreestanding -march=i386 -nostdlib)
set(CMAKE_CXX_COMPILER ${TARGET_GNU_PREFIX}g++ -ffreestanding -march=i386 -nostdlib -nostdinc++)
set(CMAKE_AR ${TARGET_GNU_PREFIX}ar)
set(CMAKE_LINKER "${TARGET_GNU_PREFIX}ld -nostdlib")

find_program(XORRISO xorriso) # Needed by grub-mkrescue
find_program(GRUB_MKRESCUE grub-mkrescue REQUIRED)
find_program(BOCHS bochs)
find_program(NM ${TARGET_GNU_PREFIX}nm)
find_program(OBJDUMP ${TARGET_GNU_PREFIX}objdump)
