cmake_minimum_required(VERSION 3.27)
project(unikum C)

set(CMAKE_C_STANDARD 11)

add_executable(unikum main.c)

add_subdirectory(libs)

add_library(str string/string_.h string/string_.c)
target_link_libraries(unikum str)

target_link_libraries(unikum data_structures)
target_link_libraries(unikum algorithms)
