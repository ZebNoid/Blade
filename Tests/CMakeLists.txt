project(Tests)

add_executable(${PROJECT_NAME}
        main.cpp
        Core/Expect.h
        Core/TestRunner.cpp
        Core/TestRunner.h
        Layout/LayoutAlignmentTests.cpp
        Layout/LayoutAlignmentTests.h
        Layout/LayoutConstraintsTests.cpp
        Layout/LayoutConstraintsTests.h
        Layout/LayoutFlexTests.cpp
        Layout/LayoutFlexTests.h
        Layout/LayoutPaddingTests.cpp
        Layout/LayoutPaddingTests.h
        Layout/LayoutRootModifierTests.cpp
        Layout/LayoutRootModifierTests.h
        Layout/LayoutSpacingTests.cpp
        Layout/LayoutSpacingTests.h
        Layout/LayoutStackTests.cpp
        Layout/LayoutStackTests.h
        Layout/LayoutTestUtils.h
        ModifierTree/ModifierTreeTests.cpp
        ModifierTree/ModifierTreeTests.h
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
