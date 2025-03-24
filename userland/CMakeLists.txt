add_compile_options("--sysroot=${BEETLE_SYSROOT}")
add_link_options("--sysroot=${BEETLE_SYSROOT}")

add_subdirectory(init)

add_dependencies(init c)