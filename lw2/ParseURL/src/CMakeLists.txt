add_library(parse_url_lib STATIC
        URLParser.cpp
        main.cpp)

target_include_directories(parse_url_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
