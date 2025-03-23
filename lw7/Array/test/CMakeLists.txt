include(GoogleTest)

add_executable(array_test
        Array_test.cpp
)

target_link_libraries(array_test PRIVATE GTest::GTest GTest::gtest_main)

gtest_discover_tests(array_test)
