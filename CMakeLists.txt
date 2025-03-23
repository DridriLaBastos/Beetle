cmake_minimum_required(VERSION 3.12 FATAL_ERROR) #3.12 needed to use file GLOB CONFIGURE_DEPENDS option

project(BeetleOS
		VERSION 0.0.2
		DESCRIPTION "Microkernel operating system"
		LANGUAGES C CXX ASM_NASM
		)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 11)

set(BEETLE_TARGET "" CACHE STRING "The target cpu architecture for which Beetle will be compiled")
set(BEETLE_PLATFORM "" CACHE STRING "The target platform for which Beetle will be compiled")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE true)

# include_directories("${CMAKE_SOURCE_DIR}")
# include_directories(SYSTEM "${CMAKE_SOURCE_DIR}/libc")

# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sysroot)

# set(MISC_OBJ_FILES
# 	${PROJECT_BINARY_DIR}/libc/misc/crt0.o
# 	${PROJECT_BINARY_DIR}/libc/misc/crti.o
# 	${PROJECT_BINARY_DIR}/libc/misc/crtn.o
# )

# add_subdirectory(libc)

add_subdirectory(beetle)
add_subdirectory(services)

file(WRITE ${PROJECT_BINARY_DIR}/grub.cfg
		"menuentry \"${BEETLE_PROJECT_NAME_REVISION}\" {
			multiboot /boot/beetle
			module /bin/pm
		}"
	)

	add_custom_command(OUTPUT beetle.iso
	COMMENT "Creating iso image"
	COMMAND ${CMAKE_COMMAND} -E rm -Rf iso
	COMMAND ${CMAKE_COMMAND} -E make_directory iso
	COMMAND ${CMAKE_COMMAND} -E copy grub.cfg iso/boot/grub/grub.cfg
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:beetle> iso/boot/beetle
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pm> iso/bin/pm
	COMMAND ${GRUB_MKRESCUE} -o ${CMAKE_SOURCE_DIR}/beetle.iso iso)
	
	# Create an iso boot image
#TODO: This should also depend on grub.cfg so that if I want to modify the content of the file it is automatically regenerated
add_custom_target(iso DEPENDS beetle.iso)

add_custom_target(run 
					COMMAND bochs -q
					WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
					DEPENDS iso)
