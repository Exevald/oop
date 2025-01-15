add_library(expand_template_lib STATIC
        main.cpp
        TemplateExpander.cpp)

target_include_directories(expand_template_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
