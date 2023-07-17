project(beetle
		VERSION 0.0.2
		DESCRIPTION "The kernel for BeetleOS")

include_directories(include)

# add_compile_options also add compile options for the nasm compiler and we don't want that
set(COMMON_FLAGS "-ffreestanding -fno-stack-protector")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -fno-exceptions -fno-rtti -nostdinc++")

add_link_options(-nostdlib)

add_subdirectory(arch/${TARGET})

set(BEETLE_PROJECT_NAME_REVISION "${PROJECT_NAME}.${PROJECT_VERSION}")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/iso/bin)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB ASM_SOURCES CONFIGURE_DEPENDS "*.asm")

add_executable(beetle ${CXX_SOURCES} ${ASM_SOURCES} $<TARGET_OBJECTS:${TARGET}>)

file(WRITE ${PROJECT_BINARY_DIR}/iso/boot/grub/grub.cfg
		"menuentry \"${BEETLE_PROJECT_NAME_REVISION}\" {
			multiboot /boot/beetle
			# module /bin/pmn.elf \"bonjour comment tu vas ?\"
		}"
	)

target_link_libraries(beetle PRIVATE kernelc)

target_link_options(beetle
					PRIVATE -Wl,--script=${PROJECT_SOURCE_DIR}/linker.ld
					)

target_compile_definitions(beetle PUBLIC BEETLE_PMN_NAME="${BEETLE_PMN_NAME}" BEETLE_VERSION_NAME="Beetle v${PROJECT_VERSION}")

add_custom_command(TARGET beetle POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E echo "* * * CREATING ISO * * *"
					COMMAND ${SIZE_EXEC} $<TARGET_FILE:beetle>
					COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:beetle> iso/boot/$<TARGET_FILE_NAME:beetle>
					# # COMMAND ${CMAKE_COMMAND} -E copy ${PMN_BINARY_PATH} iso/bin/pmn.elf
					COMMAND ${GRUB_MKRESCUE} ARGS -o ${CMAKE_SOURCE_DIR}/beetle.iso iso
					COMMAND ${NM} --demangle --numeric-sort $<TARGET_FILE:beetle> > ${CMAKE_SOURCE_DIR}/tmps.txt
					COMMAND ${OBJDUMP} -d -M intel $<TARGET_FILE:beetle> > ${CMAKE_SOURCE_DIR}/tmpd.txt
					BYPRODUCTS beetle.iso
					)

add_custom_target(run COMMAND bochs -q
					WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
					DEPENDS beetle)