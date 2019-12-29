cmake_minimum_required(VERSION 3.5)

project(libc7)
add_compile_options(-std=c99 -Wall -Werror -O2 -g)

file(GLOB_RECURSE sources source/c7/*.c)

add_library(lib_static STATIC ${sources})
set_target_properties(lib_static PROPERTIES OUTPUT_NAME c7)
target_include_directories(lib_static PUBLIC source/)

add_executable(tests ${sources} source/tests.c)
target_include_directories(tests PUBLIC source/)

file(GLOB headers source/c7/*.h)
install(FILES ${headers} DESTINATION include/c7)

install(FILES build/libc7.a DESTINATION lib)

