include(GoogleTest)

add_executable(http_url_test
        HttpURL_test.cpp
)

target_link_libraries(http_url_test PRIVATE GTest::GTest GTest::gtest_main http_url_lib)

gtest_discover_tests(http_url_test)
