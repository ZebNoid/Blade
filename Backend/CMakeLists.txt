project(Backend)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        App/AppBackend.cpp
        App/AppBackend.h

        WinApi/NativeApp/NativeApp.cpp
        WinApi/NativeApp/NativeApp.h

        WinApi/ClassRegistry/WindowClass.cpp
        WinApi/ClassRegistry/WindowClass.h
        WinApi/Hwnd/Hwnd.cpp
        WinApi/Hwnd/Hwnd.h

        WinApi/WindowProc/WindowProc.cpp
        WinApi/WindowProc/WindowProc.h
        WinApi/MessageRouter/MessageRouter.cpp
        WinApi/MessageRouter/MessageRouter.h

        Window/NativeWindow.cpp
        Window/NativeWindow.h

        Node/WinNode/WinNode.cpp
        Node/WinNode/WinNode.h
        Node/NativeNode/NativeNode.cpp
        Node/NativeNode/NativeNode.h
        WinApi/WindowHost/WindowHost.cpp
        WinApi/WindowHost/WindowHost.h

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
        Api # Blade API
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
