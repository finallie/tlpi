cmake_minimum_required(VERSION 3.16)
project(tlpi C)

set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ../bin)

add_executable(hellowold main.c)
target_link_libraries(hellowold tlpi)


add_executable(4_1 4/1.c)
target_link_libraries(4_1 tlpi)
add_executable(4_2 4/2.c)
target_link_libraries(4_2 tlpi)