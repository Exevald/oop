cmake_minimum_required(VERSION 3.27)
project(calculator_lib)

add_library(calculator_lib STATIC
        main.cpp)

add_executable(
        calculator
        main.cpp
)

target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
