add_library(string_lib STATIC
        CString.cpp
)

target_include_directories(string_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
