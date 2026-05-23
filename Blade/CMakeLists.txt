project(Blade VERSION 0.3.1)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        App/App.cpp
        App/App.h

        Base/Widget.h
        Base/RootWidget.h
        Base/WidgetTree.h

        Widget/Window/Window.h
        Widget/Window/WindowProps.h
        Widget/Window/WindowEvents.h

        Widget/Button/Button.h
        Widget/Button/ButtonProps.h
        Widget/Button/ButtonEvents.h

        Widget/Layout/Column/Column.h
        Widget/Layout/Column/ColumnProps.h
        Widget/Layout/Row/Row.h
        Widget/Layout/Row/RowProps.h
        Widget/Layout/Stack/Stack.h
        Widget/Layout/Stack/StackProps.h

        Runtime/Materializer/Materializer.cpp
        Runtime/Materializer/Materializer.h
        Runtime/LayoutRuntime/LayoutRuntime.cpp
        Runtime/LayoutRuntime/LayoutRuntime.h
        Runtime/Normalize/Normalize.h
        Runtime/Normalize/NormalizedProps.h
        Runtime/Normalize/PropsVisitor.h
        Runtime/Normalize/EventVisitor.h
        Runtime/LayoutEngine/Data/LayoutNode.h
        Runtime/LayoutEngine/Data/LayoutContext.h
        Runtime/LayoutEngine/Algorithm/LayoutLeaf.cpp
        Runtime/LayoutEngine/Algorithm/LayoutLeaf.h
        Runtime/LayoutEngine/Algorithm/LayoutColumn.cpp
        Runtime/LayoutEngine/Algorithm/LayoutColumn.h
        Runtime/LayoutEngine/Algorithm/LayoutRow.cpp
        Runtime/LayoutEngine/Algorithm/LayoutRow.h
        Runtime/LayoutEngine/Algorithm/LayoutStack.cpp
        Runtime/LayoutEngine/Algorithm/LayoutStack.h
        Runtime/LayoutEngine/LayoutEngine/LayoutEngine.cpp
        Runtime/LayoutEngine/LayoutEngine/LayoutEngine.h
        Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.cpp
        Runtime/LayoutEngine/LayoutTreeBuilder/LayoutTreeBuilder.h
        Runtime/LayoutEngine/Data/LayoutData.h

        Props/LayoutProps/CrossAxisAlignment.h
        Props/LayoutProps/MainAxisAlignment.h
        Runtime/LayoutEngine/Data/LayoutType.h
)

# use Unicode
with_unicode(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link required WinAPI libraries
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Api
        user32
        gdi32
        comctl32
        uxtheme #include <uxtheme.h>
)

# TODO remove?
target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        pch.h
)

# TODO fix include
#target_compile_options(Blade PRIVATE /W4)
