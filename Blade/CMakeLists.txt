project(Blade VERSION 0.2.4)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        App/App.cpp
        App/App.h
        Widget/Widget.cpp
        Widget/Widget.h

        Widget/Window/Window.cpp
        Widget/Window/Window.h
        Widget/Window/WindowProps.h
        Widget/Window/WindowEvents.h

        Widget/Button/Button.cpp
        Widget/Button/Button.h
        Widget/Button/ButtonProps.h
        Widget/Button/ButtonEvents.h
        Runtime/Materializer/Materializer.cpp
        Runtime/Materializer/Materializer.h

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
