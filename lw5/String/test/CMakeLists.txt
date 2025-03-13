include(GoogleTest)

add_executable(string_test
        String_test.cpp
)

target_link_libraries(string_test PRIVATE GTest::GTest GTest::gtest_main string_lib)

gtest_discover_tests(string_test)
