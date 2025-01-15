include(GoogleTest)

add_executable(expand_template_test ExpandTemplate_test.cpp)

target_link_libraries(expand_template_test PRIVATE GTest::GTest GTest::gtest_main expand_template_lib)

gtest_discover_tests(expand_template_test)
