project(Tests)

add_executable(${PROJECT_NAME}
        main.cpp
        Layout/LayoutPaddingTests.cpp
        Layout/LayoutPaddingTests.h
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Blade
)
