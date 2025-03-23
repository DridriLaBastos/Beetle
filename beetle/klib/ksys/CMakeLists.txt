project(Ksys DESCRIPTION "Set of helper functions that provide target dependant features")

add_library(ksys STATIC src/${BEETLE_TARGET}/io.c)

target_include_directories(ksys SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/include)
