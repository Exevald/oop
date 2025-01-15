include(GoogleTest)

add_executable(parse_url_test ParseURL_test.cpp)

target_link_libraries(parse_url_test PRIVATE GTest::GTest GTest::gtest_main parse_url_lib)

gtest_discover_tests(parse_url_test)
