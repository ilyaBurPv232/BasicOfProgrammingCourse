cmake_minimum_required(VERSION 3.27)
project(unikum C)

set(CMAKE_C_STANDARD 11)

add_executable(unikum main.c)

add_subdirectory(libs)
target_link_libraries(unikum data_structures)
target_link_libraries(unikum algorithms)