project(BEETLE_PMN
		VERSION 0.0.1
		DESCRIPTION "Default process managment program of beetle")

file(GLOB C_SRC CONFIGURE_DEPENDS *.c)

add_executable(pmn.elf ${C_SRC})
