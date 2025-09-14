project("Beetle libC")

add_library(crt0 OBJECT src/misc/crt0.c)
add_library(crti OBJECT src/misc/crti.asm)
add_library(crtn OBJECT src/misc/crtn.asm)

add_library(c STATIC src/string.c)
add_dependencies(c crti crt0 crtn)

file(GLOB LIBC_STANDARD_HEADERS ${PROJECT_SOURCE_DIR}/include/*.h)

target_include_directories(c PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Remaking a sysroot
# On my developments machine, some version of gcc asks for a libc.a or a libg.a. Both version should be a c library
add_custom_command(TARGET c POST_BUILD
	COMMENT "* * * Preparing User Land Sysroot * * *"
	# Preparing the sysroot directory
	COMMAND ${CMAKE_COMMAND} -E rm -Rf ${BEETLE_SYSROOT}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BEETLE_SYSROOT_USR_INCLUDE}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${BEETLE_SYSROOT_USR_LIB}

	# Populating the sysroot directory
	COMMAND ${CMAKE_COMMAND} -E copy ${LIBC_STANDARD_HEADERS} ${BEETLE_SYSROOT_USR_INCLUDE}
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${BEETLE_SYSROOT_USR_LIB}/libc.a
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:c> ${BEETLE_SYSROOT_USR_LIB}/libg.a

	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crt0> ${BEETLE_SYSROOT_USR_LIB}/crt0.o
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crti> ${BEETLE_SYSROOT_USR_LIB}/crti.o
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crtn> ${BEETLE_SYSROOT_USR_LIB}/crtn.o
	)
