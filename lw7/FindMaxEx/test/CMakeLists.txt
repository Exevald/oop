include(GoogleTest)

add_executable(find_max_test
        FindMax_test.cpp
)

target_link_libraries(find_max_test PRIVATE GTest::GTest GTest::gtest_main)

gtest_discover_tests(find_max_test)
