include(GoogleTest)

add_executable(shapes_test
        Shapes_test.cpp
        Rectangle_test.cpp
        Triangle_test.cpp
        Circle_test.cpp
        LineSegment_test.cpp
)

target_link_libraries(shapes_test PRIVATE GTest::GTest GTest::gtest_main shapes_lib)

gtest_discover_tests(shapes_test)
