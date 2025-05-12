project(init)

add_executable(init main.c)

target_compile_options(init PRIVATE "-fPIE")
target_link_options(init PRIVATE "-pie")
