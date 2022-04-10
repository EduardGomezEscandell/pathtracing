cmake_minimum_required(VERSION 3.16)

project(pathtracer LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

add_subdirectory(external_libraries)
add_subdirectory(src)
add_subdirectory(test)