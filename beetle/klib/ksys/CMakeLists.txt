project(Ksys DESCRIPTION "Set of helper functions that provide target dependant features")

include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src/${BEETLE_TARGET})

add_library(ksys STATIC $<TARGET_OBJECTS:ksys_${BEETLE_TARGET}>)

target_include_directories(ksys SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/include)
