project(BEETLE_PMN
		VERSION 0.0.1
		DESCRIPTION "Default process managment program of beetle")

file(GLOB CPP_SRC CONFIGURE_DEPENDS *.cpp)

add_executable(pmn.elf ${CPP_SRC})
