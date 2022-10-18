project("Beetle libC" C)

file(GLOB LIBC_C_SRC CONFIGURE_DEPENDS *.c)

add_library(c ${LIBC_C_SRC} include/stdint.h)
