cmake_minimum_required(VERSION 3.27)
project(bank)

add_library(bank_lib STATIC
        CBank.cpp
        CSimulation.cpp
        main.cpp
)

add_executable(bank
        CBank.cpp
        CSimulation.cpp
        main.cpp
)

target_include_directories(bank_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})