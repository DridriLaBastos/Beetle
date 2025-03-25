add_compile_options("--sysroot=${BEETLE_SYSROOT}")
add_link_options("--sysroot=${BEETLE_SYSROOT}")

add_subdirectory(init)

# We need to be sure that the C library has been compiled and a sysroot has been created before we can
# compile each userland program. We are using default arguments of the compiler toolchain and not manually
# giving -lc flags to each target. The compiler toolchain will automatically checks for its needed include
# files inside 'sysroot/usr/include' and the needed libraries inside 'sysroot/usr/lib'. Thus, those folders
# need to be populate with the required contents before we can compile the userland programs. The creation
# of the sysroot directories is done after the libc has been compiled thus we need to create the manual
# dependency because without the target_link_library, cmake will not create it by default.
add_dependencies(init c)
