project(Backend)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        App/AppBackend.cpp
        App/AppBackend.h

        WindowHost/WindowHost.cpp
        WindowHost/WindowHost.h

        WinApi/ClassRegistry/WindowClass.cpp
        WinApi/ClassRegistry/WindowClass.h
        WinApi/Hwnd/Hwnd.cpp
        WinApi/Hwnd/Hwnd.h

        WinApi/WindowProc/WindowProc.cpp
        WinApi/WindowProc/WindowProc.h
        WinApi/MessageRouter/MessageRouter.cpp
        WinApi/MessageRouter/MessageRouter.h
        WinApi/CommandRouter/CommandRouter.cpp
        WinApi/CommandRouter/CommandRouter.h

        WinApi/AppRuntime/AppRuntime.cpp
        WinApi/AppRuntime/AppRuntime.h

        WinApi/Window/NativeWindow.cpp
        WinApi/Window/NativeWindow.h

        WinApi/NativeApi/NativeApi.cpp
        WinApi/NativeApi/NativeApi.h

        Node/NativeNode/NativeNode.cpp
        Node/NativeNode/NativeNode.h
        Node/NodeRegistry/NodeRegistry.cpp
        Node/NodeRegistry/NodeRegistry.h
        Node/NativeNodeFactory/NativeNodeFactory.cpp
        Node/NativeNodeFactory/NativeNodeFactory.h

        CommandDispatcher/CommandDispatcher.cpp
        CommandDispatcher/CommandDispatcher.h
        Event/EventMapper/EventMapper.cpp
        Event/EventMapper/EventMapper.h
        Property/NativePropertyMapper/NativePropertyMapper.cpp
        Property/NativePropertyMapper/NativePropertyMapper.h
        WinApi/CommonControls/CommonControls.cpp
        WinApi/CommonControls/CommonControls.h
        WinApi/INativeElement/INativeElement.h

        Components/Button/NativeButton.cpp
        Components/Button/NativeButton.h
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
