cmake_minimum_required(VERSION 3.16)

project(pathtracer LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external_libraries)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(demos)
