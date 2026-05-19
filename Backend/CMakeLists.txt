project(Backend)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        backend.h
        WinBackend/WinBackend.cpp
        WinBackend/WinBackend.h
        WinInit/WinInit.cpp
        WinInit/WinInit.h
        WinWindow/WinWindow.cpp
        WinWindow/WinWindow.h

        Handlers/CommandHandler/CommandHandler.cpp
        Handlers/CommandHandler/CommandHandler.h
        Handlers/InputHandler/InputHandler.cpp
        Handlers/InputHandler/InputHandler.h
        Handlers/WindowHandler/WindowHandler.cpp
        Handlers/WindowHandler/WindowHandler.h
        Handlers/PaintHandler/PaintHandler.cpp
        Handlers/PaintHandler/PaintHandler.h

        Debug/LayoutDebugRenderer/LayoutDebugRenderer.cpp
        Debug/LayoutDebugRenderer/LayoutDebugRenderer.h
        Debug/LayoutDebugTheme.h
        Debug/DebugPainter/DebugPainter.cpp
        Debug/DebugPainter/DebugPainter.h
        Debug/NativeDraw/NativeDraw.cpp
        Debug/NativeDraw/NativeDraw.h
        Debug/DebugProps.h
        Debug/DebugBrushProps.h

        Widget/WinWidget/WinWidget.cpp
        Widget/WinWidget/WinWidget.h
        Widget/WinCustom/WinCustom.h
        Widget/WinCustom/WinCustom.cpp
        Widget/WinRender/WinRender.cpp
        Widget/WinRender/WinRender.h
        Registry/ClassRegistry/ClassRegistry.cpp
        Registry/ClassRegistry/ClassRegistry.h
        Registry/ResourceRegistry/ResourceRegistry.h
        Registry/ResourceRegistry/ResourceRegistry.cpp
        Widget/WinLabel/WinLabel.h
        Widget/WinLabel/WinLabel.cpp
        Widget/WinNop/WinNop.h
        Widget/WinNop/WinNop.cpp
        Materializer/Materializer.cpp
        Materializer/Materializer.h
        Helpers/WinUtils.h
        Widget/WinButton/WinButton.cpp
        Widget/WinButton/WinButton.h
        Widget/WinCheckbox/WinCheckbox.h
        Widget/WinCheckbox/WinCheckbox.cpp
        Widget/WinProgress/WinProgress.cpp
        Widget/WinProgress/WinProgress.h
        Widget/WinRadioButton/WinRadioButton.cpp
        Widget/WinRadioButton/WinRadioButton.h
        Widget/WinSlider/WinSlider.h
        Widget/WinSlider/WinSlider.cpp
        Widget/WinTextField/WinTextField.cpp
        Widget/WinTextField/WinTextField.h
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
        Blade # Blade API
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
