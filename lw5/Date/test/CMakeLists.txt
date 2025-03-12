include(GoogleTest)

add_executable(date_test
        Date_test.cpp
)

target_link_libraries(date_test PRIVATE GTest::GTest GTest::gtest_main date_lib)

gtest_discover_tests(date_test)
