include(GoogleTest)

add_executable(lru_cache_test
        LRUCache_test.cpp
)

target_link_libraries(lru_cache_test PRIVATE GTest::GTest GTest::gtest_main)

gtest_discover_tests(lru_cache_test)
