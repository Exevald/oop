cmake_minimum_required(VERSION 3.27)
project(oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()

add_subdirectory(lw2)
add_subdirectory(lw3)
add_subdirectory(lw4/Shapes)
add_subdirectory(lw5)
add_subdirectory(lw6)