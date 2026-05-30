project(Tests)

add_executable(${PROJECT_NAME}
        main.cpp
        Core/Expect.h
        Layout/LayoutAlignmentTests.cpp
        Layout/LayoutAlignmentTests.h
        Layout/LayoutConstraintsTests.cpp
        Layout/LayoutConstraintsTests.h
        Layout/LayoutPaddingTests.cpp
        Layout/LayoutPaddingTests.h
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Blade
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER Tests)
