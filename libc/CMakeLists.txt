project("Beetle libC")

add_library(crt0 OBJECT src/misc/crt0.c)
add_library(crti OBJECT src/misc/crti.asm)
add_library(crtn OBJECT src/misc/crtn.asm)

add_library(c STATIC $<TARGET_OBJECTS:crt0> $<TARGET_OBJECTS:crti> $<TARGET_OBJECTS:crtn>)

file(GLOB LIBC_STANDARD_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

target_include_directories(c PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Remaking a sysroot
# On my developments machine, some version of gcc asks for a libc.a or a libg.a. Both version should be a c library
add_custom_command(TARGET c POST_BUILD
	COMMENT "* * * Preparing User Land Sysroot * * *"
	# COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crt0.c.obj ${CMAKE_SYSROOT_USR_LIB}/crt0.o
	# COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crti.asm.obj ${CMAKE_SYSROOT_USR_LIB}/crti.o
	# COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/CMakeFiles/misc.dir/src/misc/crtn.asm.obj ${CMAKE_SYSROOT_USR_LIB}/crtn.o
	COMMAND ${CMAKE_COMMAND} -E copy ${LIBC_STANDARD_HEADERS} ${BEETLE_SYSROOT_USR_INCLUDE}
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${BEETLE_SYSROOT_USR_LIB}/libc.a
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${BEETLE_SYSROOT_USR_LIB}/libg.a

	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crt0> ${BEETLE_SYSROOT_USR_LIB}/crt0.o
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crti> ${BEETLE_SYSROOT_USR_LIB}/crti.o
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crtn> ${BEETLE_SYSROOT_USR_LIB}/crtn.o
	)
