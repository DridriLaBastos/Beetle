project(BEETLE_PMN
		VERSION 0.0.1
		DESCRIPTION "Default process management server of Beetle")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(pm main.cpp)

target_compile_options(pm PRIVATE -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti -nostdinc++)
target_link_options(pm PRIVATE -nostdlib -lgcc -pie)
