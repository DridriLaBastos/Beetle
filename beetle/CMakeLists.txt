project(beetle
		VERSION 0.0.2
		DESCRIPTION "The kernel for BeetleOS")

include_directories(include)

add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:-ffreestanding>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>)

add_link_options(-nostdlib)

add_subdirectory(arch/${TARGET})

set(BEETLE_PMN_NAME "pmn.elf")

set(BEETLE_PROJECT_NAME_REVISION "${PROJECT_NAME}.${PROJECT_VERSION}")
set(BEETLE_ISO_FILE_PATH ${CMAKE_CURRENT_BINARY_DIR}/${BEETLE_PROJECT_NAME_REVISION})

file(WRITE ${PROJECT_BINARY_DIR}/iso/boot/grub/grub.cfg
		"menuentry \"${BEETLE_PROJECT_NAME_REVISION}\" {
			multiboot /boot/beetle.elf
		}"
	)
#module /bin/pmn.elf \"${BEETLE_PMN_NAME}\"
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/iso/bin)

file(GLOB CXX_SOURCES CONFIGURE_DEPENDS "*.cpp")
file(GLOB ASM_NASM_SOURCES CONFIGURE_DEPENDS "*.s")

foreach(asm_file ${ASM_NASM_SOURCES})
	set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM_NASM)
endforeach(asm_file ${ASM_NASM_SOURCES})

add_executable(beetle.elf ${CXX_SOURCES} ${ASM_NASM_SOURCES} $<TARGET_OBJECTS:${TARGET}>)

target_link_libraries(beetle.elf c)

target_link_options(beetle.elf
					PRIVATE -Wl,--script=${PROJECT_SOURCE_DIR}/linker.ld
					)

target_compile_definitions(beetle.elf PUBLIC BEETLE_PMN_NAME="${BEETLE_PMN_NAME}" BEETLE_VERSION_NAME="Beetle v${PROJECT_VERSION}")

add_custom_command(TARGET beetle.elf POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy beetle.elf iso/boot/beetle.elf
					#COMMAND ${CMAKE_COMMAND} -E copy services/process_manager/pmn.elf iso/bin/pmn.elf
					COMMAND ${GRUB_MKRESCUE} ARGS -o beetle.iso iso
					COMMAND ${NM} --demangle --numeric-sort beetle.elf > ${PROJECT_SOURCE_DIR}/../tmps.txt
					COMMAND ${OBJDUMP} -d -M intel beetle.elf > ${PROJECT_SOURCE_DIR}/../tmpd.txt
					BYPRODUCTS beetle.iso
					)

# Creating the bochs configuration file
file(WRITE ${CMAKE_SOURCE_DIR}/.bochsrc
"ata0-master: type=cdrom, path=${PROJECT_BINARY_DIR}/beetle.iso, status=inserted
boot: cdrom
cpu: model= bx_generic, reset_on_triple_fault=true
log: BeetleOS.log
magic_break: enabled=1
")

add_custom_target(run COMMAND bochs -q
					WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
					DEPENDS beetle.elf)