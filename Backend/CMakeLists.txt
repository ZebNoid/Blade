project(Backend)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        App/AppBackend.cpp
        App/AppBackend.h
        AppCommandDispatcher/AppCommandDispatcher.cpp
        AppCommandDispatcher/AppCommandDispatcher.h
        UI/UI.h
        Resource/ResourceManager/ResourceManager.cpp
        Resource/ResourceManager/ResourceManager.h
        Render/RenderNode/RenderNode.h
        Render/RenderRegistry/RenderRegistry.cpp
        Render/RenderRegistry/RenderRegistry.h
        Render/RenderCommandDispatcher/RenderCommandDispatcher.cpp
        Render/RenderCommandDispatcher/RenderCommandDispatcher.h
        Render/VirtualElementState/VirtualElementState.h
        Render/WindowSurfaceRuntime/WindowSurfaceRuntime.cpp
        Render/WindowSurfaceRuntime/WindowSurfaceRuntime.h

        WindowHost/WindowHost.cpp
        WindowHost/WindowHost.h

        WinApi/Window/WindowClass/WindowClass.cpp
        WinApi/Window/WindowClass/WindowClass.h
        WinApi/Window/Hwnd/Hwnd.cpp
        WinApi/Window/Hwnd/Hwnd.h
        WinApi/Window/WindowProc/WindowProc.cpp
        WinApi/Window/WindowProc/WindowProc.h
        WinApi/Router/MessageRouter/MessageRouter.cpp
        WinApi/Router/MessageRouter/MessageRouter.h
        WinApi/Router/CommandRouter/CommandRouter.cpp
        WinApi/Router/CommandRouter/CommandRouter.h

        WinApi/AppRuntime/AppRuntime.cpp
        WinApi/AppRuntime/AppRuntime.h
        WinApi/Interop/ComScope/ComScope.cpp
        WinApi/Interop/ComScope/ComScope.h
        WinApi/Interop/OleScope/OleScope.cpp
        WinApi/Interop/OleScope/OleScope.h
        WinApi/OleDragDrop/OleDropTarget/OleDropTarget.cpp
        WinApi/OleDragDrop/OleDropTarget/OleDropTarget.h
        WinApi/Menu/NativeContextMenu/NativeContextMenu.cpp
        WinApi/Menu/NativeContextMenu/NativeContextMenu.h
        WinApi/HwndApi/HwndApi.cpp
        WinApi/HwndApi/HwndApi.h
        WinApi/Display/DisplayApi/DisplayApi.cpp
        WinApi/Display/DisplayApi/DisplayApi.h
        WinApi/Theme/ThemeApi/ThemeApi.cpp
        WinApi/Theme/ThemeApi/ThemeApi.h
        WinApi/Render/GdiPlusScope/GdiPlusScope.cpp
        WinApi/Render/GdiPlusScope/GdiPlusScope.h
        WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.cpp
        WinApi/Render/GdiPlusRenderApi/GdiPlusRenderApi.h
        WinApi/Render/RenderApi/RenderApi.cpp
        WinApi/Render/RenderApi/RenderApi.h
        WinApi/Resource/ImageLoader/ImageLoader.cpp
        WinApi/Resource/ImageLoader/ImageLoader.h
        WinApi/Resource/FontApi/FontApi.cpp
        WinApi/Resource/FontApi/FontApi.h
        WinApi/Resource/IconImageLoader/IconImageLoader.cpp
        WinApi/Resource/IconImageLoader/IconImageLoader.h
        WinApi/Resource/WicImageLoader/WicImageLoader.cpp
        WinApi/Resource/WicImageLoader/WicImageLoader.h
        WinApi/NativeElement/NativeElement.cpp
        WinApi/NativeElement/NativeElement.h

        Node/NativeNode/NativeNode.cpp
        Node/NativeNode/NativeNode.h
        Node/NativeCreateContext/NativeCreateContext.h
        Node/NativeBindingRegistry/NativeBindingRegistry.cpp
        Node/NativeBindingRegistry/NativeBindingRegistry.h
        Node/NodeRegistry/NodeRegistry.cpp
        Node/NodeRegistry/NodeRegistry.h
        Node/NativeFactoryRegistry/NativeFactoryRegistry.cpp
        Node/NativeFactoryRegistry/NativeFactoryRegistry.h
        Node/NativeNodeFactory/NativeNodeFactory.cpp
        Node/NativeNodeFactory/NativeNodeFactory.h

        CommandDispatcher/CommandDispatcher.cpp
        CommandDispatcher/CommandDispatcher.h
        Event/EventMapper/EventMapper.cpp
        Event/EventMapper/EventMapper.h
        Property/PropertyMapper/PropertyMapper.cpp
        Property/PropertyMapper/PropertyMapper.h
        Property/PropertyReader.h
        WinApi/NativeElement/INativeElement.h

        Components/Window/NativeWindow.cpp
        Components/Window/NativeWindow.h
        Components/Window/NativeWindowApi/NativeWindowApi.cpp
        Components/Window/NativeWindowApi/NativeWindowApi.h
        Components/Window/NativeWindowPlacement/NativeWindowPlacement.cpp
        Components/Window/NativeWindowPlacement/NativeWindowPlacement.h
        Components/Window/NativeWindowStyle/NativeWindowStyle.cpp
        Components/Window/NativeWindowStyle/NativeWindowStyle.h
        Components/Window/NativeWindowEvents.cpp
        Components/Window/NativeWindowEvents.h
        Components/Window/NativeWindowProps.cpp
        Components/Window/NativeWindowProps.h
        Components/Window/NativeWindowPropsData/NativeWindowPropsData.cpp
        Components/Window/NativeWindowPropsData/NativeWindowPropsData.h
        Components/Tray/NativeTray.cpp
        Components/Tray/NativeTray.h
        Components/Tray/NativeTrayApi/NativeTrayApi.cpp
        Components/Tray/NativeTrayApi/NativeTrayApi.h
        Components/RenderSurface/RenderSurface.cpp
        Components/RenderSurface/RenderSurface.h
        Components/Native/Label/NativeLabel.cpp
        Components/Native/Label/NativeLabel.h
        Components/Native/Button/NativeButton.cpp
        Components/Native/Button/NativeButton.h
        Components/Native/Button/NativeButtonApi/NativeButtonApi.cpp
        Components/Native/Button/NativeButtonApi/NativeButtonApi.h
        Components/Native/Button/NativeButtonProps.cpp
        Components/Native/Button/NativeButtonProps.h
        Components/Native/Button/NativeButtonEvents.cpp
        Components/Native/Button/NativeButtonEvents.h
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
        gdiplus
        comctl32
        uxtheme #include <uxtheme.h>
        windowscodecs # png
        ole32
        shell32
)

# TODO remove?
target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        pch.h
)

# TODO fix include
#target_compile_options(Blade PRIVATE /W4)
