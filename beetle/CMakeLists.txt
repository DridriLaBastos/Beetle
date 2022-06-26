set(BEETLE_KERNEL_VERSION 0.0.2)

project(beetle
		VERSION ${BEETLE_KERNEL_VERSION}
		DESCRIPTION "The kernel for BeetleOS")

include_directories(include)
add_subdirectory(arch/${TARGET})
add_subdirectory(services)

file(WRITE ${PROJECT_BINARY_DIR}/iso/boot/grub/grub.cfg
"menuentry \"Beetle ${BEETLE_KERNEL_VERSION}\" {
	multiboot /boot/beetle.elf
	module /bin/pmn.elf
}"
)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/iso/bin)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB ASM_NASM_SOURCES CONFIGURE_DEPENDS "*.s")

foreach(asm_file ${ASM_NASM_SOURCES})
	set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM_NASM)
endforeach(asm_file ${ASM_NASM_SOURCES})

add_executable(beetle.elf ${CXX_SOURCES} ${ASM_NASM_SOURCES})
add_dependencies(beetle.elf pmn.elf)

target_link_options(beetle.elf
					PRIVATE -Wl,--script=${PROJECT_SOURCE_DIR}/linker.ld
					)
target_link_libraries(beetle.elf ${TARGET})

target_compile_definitions(beetle.elf PUBLIC BEETLE_PMN_NAME="pmn.elf")

add_custom_command(TARGET beetle.elf POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy beetle.elf iso/boot/beetle.elf
					COMMAND ${CMAKE_COMMAND} -E copy services/process_manager/pmn.elf iso/bin/pmn.elf
					COMMAND ${GRUB_MKRESCUE} ARGS -o beetle.iso iso
					COMMAND ${NM} --demangle --numeric-sort beetle.elf > ${PROJECT_SOURCE_DIR}/../tmps.txt
					COMMAND ${OBJDUMP} -d -M intel beetle.elf > ${PROJECT_SOURCE_DIR}/../tmpd.txt
					BYPRODUCTS beetle.iso
					)
