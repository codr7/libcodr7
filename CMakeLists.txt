cmake_minimum_required(VERSION 3.5)

project(libcodr7)
add_compile_options(-std=c11 -Wall -Werror)

file(GLOB_RECURSE sources source/codr7/*.c)

add_library(lib_static STATIC ${sources})
set_target_properties(lib_static PROPERTIES OUTPUT_NAME codr7)
target_include_directories(lib_static PUBLIC source/)

add_executable(tests ${sources} source/tests.c)
target_compile_options(tests PUBLIC -fsanitize=undefined -O2 -g)
target_include_directories(tests PUBLIC source/)
target_link_libraries(tests pthread ubsan)

add_executable(chan ${sources} bench/chan.c)
target_compile_options(chan PUBLIC -O3)
target_include_directories(chan PUBLIC source/)
target_link_libraries(chan pthread)

file(GLOB headers source/codr7/*.h)
install(FILES ${headers} DESTINATION include/codr7)

install(FILES build/libcodr7.a DESTINATION lib)

