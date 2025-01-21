include(GoogleTest)

add_executable(calculator_test
        CalculatorController_test.cpp
)

target_link_libraries(calculator_test PRIVATE GTest::GTest GTest::gtest_main calculator_lib)

gtest_discover_tests(calculator_test)
