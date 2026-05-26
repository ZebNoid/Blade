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
        WinApi/Router/MessageRouter/MessageRouter.cpp
        WinApi/Router/MessageRouter/MessageRouter.h
        WinApi/Router/CommandRouter/CommandRouter.cpp
        WinApi/Router/CommandRouter/CommandRouter.h

        WinApi/AppRuntime/AppRuntime.cpp
        WinApi/AppRuntime/AppRuntime.h

        WinApi/NativeApi/NativeApi.cpp
        WinApi/NativeApi/NativeApi.h
        WinApi/DisplayApi/DisplayApi.cpp
        WinApi/DisplayApi/DisplayApi.h
        WinApi/NativeElement/NativeElement.cpp
        WinApi/NativeElement/NativeElement.h

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
        Property/PropertyMapper/PropertyMapper.cpp
        Property/PropertyMapper/PropertyMapper.h
        WinApi/CommonControls/CommonControls.cpp
        WinApi/CommonControls/CommonControls.h
        WinApi/NativeElement/INativeElement.h

        Components/Window/NativeWindow.cpp
        Components/Window/NativeWindow.h
        Components/Window/NativeWindowApi/NativeWindowApi.cpp
        Components/Window/NativeWindowApi/NativeWindowApi.h
        Components/Window/NativeWindowEvents.cpp
        Components/Window/NativeWindowEvents.h
        Components/Window/NativeWindowProps.cpp
        Components/Window/NativeWindowProps.h
        Components/Button/NativeButton.cpp
        Components/Button/NativeButton.h
        Components/Button/NativeButtonProps.cpp
        Components/Button/NativeButtonProps.h
        Components/Button/NativeButtonEvents.cpp
        Components/Button/NativeButtonEvents.h
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
