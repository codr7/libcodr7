cmake_minimum_required(VERSION 3.5)

project(libcodr7)
add_compile_options(-std=c11 -Wall -Werror -fsanitize=alignment -O2 -g)

file(GLOB_RECURSE sources source/codr7/*.c)

add_library(lib_static STATIC ${sources})
set_target_properties(lib_static PROPERTIES OUTPUT_NAME codr7)
target_include_directories(lib_static PUBLIC source/)
target_link_libraries(lib_static ubsan)

add_executable(tests ${sources} source/tests.c)
target_include_directories(tests PUBLIC source/)
target_link_libraries(tests ubsan)

file(GLOB headers source/codr7/*.h)
install(FILES ${headers} DESTINATION include/codr7)

install(FILES build/libcodr7.a DESTINATION lib)

