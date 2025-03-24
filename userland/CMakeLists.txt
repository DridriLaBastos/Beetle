# TODO: Why is there a correct --sysroot option when compiling when cmake enter this file ?
# This option t should not be present and be added there as an add_compile_options command
# but when I check the compilation line there already is a --sysroot option...
add_subdirectory(init)

add_dependencies(init c)