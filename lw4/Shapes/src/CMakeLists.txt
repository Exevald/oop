cmake_minimum_required(VERSION 3.27)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(INPUTS
        ${CMAKE_SOURCE_DIR}/lw4/Shapes/src/input.txt
)

add_library(shapes_lib STATIC
        CLineSegment.cpp
        CTriangle.cpp
        CShape.cpp
        CSolidShape.cpp
        CRectangle.cpp
        CCircle.cpp
        CShapesController.cpp
        CCanvas.cpp
        CPoint.cpp
)

target_link_libraries(shapes_lib PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(shapes main.cpp)

target_link_libraries(shapes shapes_lib sfml-graphics sfml-window sfml-system)

target_include_directories(shapes_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

foreach (input ${INPUTS})
    add_custom_command(
            TARGET shapes POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${input} ${CMAKE_BINARY_DIR}/lw4/Shapes/src
    )
endforeach ()