project("Beetle libC" C)

file(GLOB LIBC_C_SRC CONFIGURE_DEPENDS src/*.c)

add_library(c ${LIBC_C_SRC} stdint.h)
