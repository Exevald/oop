project(calculator_lib)

add_library(calculator_lib STATIC
        CVariable.cpp
        CFunction.cpp
        CCalculator.cpp
        CCalculatorController.cpp
        main.cpp
)

add_executable(calculator
        CVariable.cpp
        CFunction.cpp
        CCalculator.cpp
        CCalculatorController.cpp
        main.cpp
)

target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
