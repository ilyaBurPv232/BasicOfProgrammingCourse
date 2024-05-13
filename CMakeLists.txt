cmake_minimum_required(VERSION 3.26.4)
project(BasicOfProgrammingCourse C)

set(CMAKE_C_STANDARD 11)

add_executable(BasicOfProgrammingCourse main.c)

add_subdirectory(libs)

add_library(str string/string_.h string/string_.c)
target_link_libraries(BasicOfProgrammingCourse str)

target_link_libraries(BasicOfProgrammingCourse data_structures)
target_link_libraries(BasicOfProgrammingCourse algorithms)
