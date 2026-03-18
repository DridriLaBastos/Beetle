project(beetle
		VERSION 0.0.2
		DESCRIPTION "The kernel for BeetleOS")

include_directories(SYSTEM include)

# add_compile_options also add compile options for the nasm compiler and we don't want that
set(COMMON_FLAGS "-ffreestanding -fno-stack-protector")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -fno-exceptions -fno-rtti -nostdinc++")

add_link_options(-nostdlib)

add_subdirectory(arch)

set(BEETLE_PROJECT_NAME_REVISION "${PROJECT_NAME}.${PROJECT_VERSION}" PARENT_SCOPE)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp" "src/*.cpp" "src/api/*.cpp")
file(GLOB ASM_SOURCES CONFIGURE_DEPENDS "*.asm")

add_executable(beetle ${CXX_SOURCES} ${ASM_SOURCES})

target_link_libraries(beetle PRIVATE arch)

target_link_options(beetle
					PRIVATE -Wl,--script=${PROJECT_SOURCE_DIR}/${BEETLE_TARGET}_${BEETLE_PLATFORM}_linker.ld
					)

add_custom_command(TARGET beetle POST_BUILD
					COMMENT "beetle size"
					COMMAND ${SIZE_EXEC} $<TARGET_FILE:beetle>
					)
