project("Beetle simple C Library Subset")

add_library(kc STATIC
				src/kstdio.c
				src/kprintf.c
				src/kstring.c
				src/arch/${BEETLE_TARGET}_${BEETLE_PLATFORM}.c)

target_include_directories(kc SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/include PRIVATE ${PROJECT_SOURCE_DIR})
