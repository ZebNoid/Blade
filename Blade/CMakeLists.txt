project(Blade VERSION 0.2.2)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} STATIC
        #        blade.h
        App/App.cpp
        App/App.h
        Context/AppContext.h
        Context/WidgetContext.h
        Windows/WindowManager/WindowManager.cpp
        Windows/WindowManager/WindowManager.h
        Widgets/Widget/Widget.cpp
        Widgets/Widget/Widget.h
        Widgets/Button/Button.cpp
        Widgets/Button/Button.h
        Widgets/Layout/Column/Column.cpp
        Widgets/Layout/Column/Column.h
        Windows/Window/Window.cpp
        Windows/Window/Window.h
        Backend/NativeWidget/NativeWidget.cpp
        Backend/NativeWidget/NativeWidget.h
        Backend/NativeButton/NativeButton.cpp
        Backend/NativeButton/NativeButton.h
        Widgets/Layout/Container/Container.cpp
        Widgets/Layout/Container/Container.h
        Materializer/Materializer.cpp
        Materializer/Materializer.h
        Core/Core.h
        Core/Encoding.cpp
        Core/Encoding.h
        Widgets/Label/Label.cpp
        Widgets/Label/Label.h
        Backend/NativeLabel/NativeLabel.cpp
        Backend/NativeLabel/NativeLabel.h
        Backend/Registry/ClassRegistry/ClassRegistry.cpp
        Backend/Registry/ClassRegistry/ClassRegistry.h
        Windows/EventRouter/EventRouter.cpp
        Windows/EventRouter/EventRouter.h
        Widgets/Layout/Row/Row.cpp
        Backend/NativeTextField/NativeTextField.cpp
        Widgets/TextField/TextField.cpp
        Widgets/TextField/TextField.h
        Events/WidgetEvent/WidgetEvent.h
        Events/WidgetEvent/EventKey.h
        Backend/Utils/WinApiUtils.h
        Backend/Registry/ResourceRegistry/ResourceRegistry.cpp
        Backend/Registry/ResourceRegistry/ResourceRegistry.h
        WidgetsProps/Widget/ColumnProps.h
        WidgetsProps/Widget/LabelProps.h
        WidgetsProps/Window/WindowProps.h
        WidgetsProps/Common/Size.h
        WidgetsProps/Common/Thickness.h
        WidgetsProps/Common/Point.h
        WidgetsProps/Common/TextAlign.h
        WidgetsProps/Widget/ButtonProps.h
        WidgetsProps/Common/StyleProps.h
        Backend/NativeCheckbox/NativeCheckbox.cpp
        Backend/NativeCheckbox/NativeCheckbox.h
        Widgets/Checkbox/Checkbox.cpp
        Widgets/Checkbox/Checkbox.h
        WidgetsProps/Widget/CheckboxProps.h
        Backend/NativeRadioButton/NativeRadioButton.cpp
        Backend/NativeRadioButton/NativeRadioButton.h
        Widgets/RadioButton/RadioButton.cpp
        Widgets/RadioButton/RadioButton.h
        WidgetsProps/Widget/RadioButtonProps.h
        WidgetsProps/Widget/TextFieldProps.h
        WidgetsProps/LayoutProps/MainAxisAlignment.h
        WidgetsProps/LayoutProps/CrossAxisAlignment.h
        Layout/LayoutFlex/LayoutFlex.cpp
        Layout/LayoutFlex/LayoutFlex.h
        Layout/LayoutFlex/FlexDirection.h
        Debug/LayoutDebugRenderer/LayoutDebugRenderer.cpp
        Debug/LayoutDebugRenderer/LayoutDebugRenderer.h
        Debug/LayoutDebugTheme.h
        Debug/DebugPainter/DebugPainter.cpp
        Debug/DebugPainter/DebugPainter.h
        Debug/NativeDraw/NativeDraw.cpp
        Debug/NativeDraw/NativeDraw.h
        Debug/DebugProps.h
        Debug/DebugBrushProps.h
        Backend/NativeProgress/NativeProgress.cpp
        Backend/NativeProgress/NativeProgress.h
        Widgets/Progress/Progress.cpp
        Widgets/Progress/Progress.h
        WidgetsProps/Widget/ProgressProps.h
        Backend/NativeSlider/NativeSlider.cpp
        Backend/NativeSlider/NativeSlider.h
        Widgets/Slider/Slider.cpp
        Widgets/Slider/Slider.h
        WidgetsProps/Widget/SliderProps.h
        Backend/Helpers/Helpers.h
        Backend/Handlers/CommandHandler/CommandHandler.cpp
        Backend/Handlers/CommandHandler/CommandHandler.h
        Backend/Handlers/InputHandler/InputHandler.cpp
        Backend/Handlers/InputHandler/InputHandler.h
        Backend/Handlers/WindowHandler/WindowHandler.cpp
        Backend/Handlers/WindowHandler/WindowHandler.h
        Backend/Handlers/PaintHandler/PaintHandler.cpp
        Backend/Handlers/PaintHandler/PaintHandler.h
        Widgets/Layout/Stack/Stack.cpp
        Widgets/Layout/Stack/Stack.h
        Layout/LayoutStack/LayoutStack.cpp
        Layout/LayoutStack/LayoutStack.h
        WidgetsEvents/Window/WindowEvents.h
        WidgetsEvents/Widget/ButtonEvents.h
        WidgetsEvents/Callback.h
        WidgetsEvents/Widget/CheckboxEvents.h
        WidgetsEvents/Widget/ProgressEvents.h
        WidgetsEvents/Widget/RadioButtonEvents.h
        WidgetsEvents/Widget/SliderEvents.h
        WidgetsEvents/Widget/TextFieldEvents.h
        Layout/LayoutEngine/LayoutEngine.cpp
        Layout/LayoutEngine/LayoutEngine.h
        Layout/LayoutEngine/LayoutType.h
        Layout/LayoutContext/LayoutContext.cpp
        Layout/LayoutContext/LayoutContext.h
        Backend/NativeCustom/NativeCustom.cpp
        Backend/NativeCustom/NativeCustom.h
        Backend/NativeNop/NativeNop.cpp
        Backend/NativeNop/NativeNop.h
        Widgets/Nop/Nop.cpp
        Widgets/Nop/Nop.h
        WidgetsProps/Widget/NopProps.h
        Render/Render.cpp
        Render/Render.h
        Backend/NativeRender/NativeRender.cpp
        Backend/NativeRender/NativeRender.h
        Core/Rect.h
        api.h
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
