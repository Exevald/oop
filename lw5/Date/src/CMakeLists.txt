add_library(date_lib STATIC
        CDate.cpp
)

target_include_directories(date_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
