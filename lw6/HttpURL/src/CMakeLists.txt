add_library(http_url_lib STATIC
        CHttpURL.cpp
)

target_include_directories(http_url_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
