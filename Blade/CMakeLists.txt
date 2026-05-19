project(Blade VERSION 0.2.3)

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
        Widgets/Layout/Container/Container.cpp
        Widgets/Layout/Container/Container.h
        Core/Core.h
        Core/Encoding.cpp
        Core/Encoding.h
        Widgets/Label/Label.cpp
        Widgets/Label/Label.h
        Windows/EventRouter/EventRouter.cpp
        Windows/EventRouter/EventRouter.h
        Widgets/Layout/Row/Row.cpp
        Widgets/TextField/TextField.cpp
        Widgets/TextField/TextField.h
        Events/WidgetEvent/WidgetEvent.h
        Events/WidgetEvent/EventKey.h
        WidgetsProps/Widget/ColumnProps.h
        WidgetsProps/Widget/LabelProps.h
        WidgetsProps/Window/WindowProps.h
        WidgetsProps/Common/Size.h
        WidgetsProps/Common/Thickness.h
        WidgetsProps/Common/Point.h
        WidgetsProps/Common/TextAlign.h
        WidgetsProps/Widget/ButtonProps.h
        WidgetsProps/Common/StyleProps.h
        Widgets/Checkbox/Checkbox.cpp
        Widgets/Checkbox/Checkbox.h
        WidgetsProps/Widget/CheckboxProps.h
        Widgets/RadioButton/RadioButton.cpp
        Widgets/RadioButton/RadioButton.h
        WidgetsProps/Widget/RadioButtonProps.h
        WidgetsProps/Widget/TextFieldProps.h
        WidgetsProps/LayoutProps/MainAxisAlignment.h
        WidgetsProps/LayoutProps/CrossAxisAlignment.h
        Layout/LayoutFlex/LayoutFlex.cpp
        Layout/LayoutFlex/LayoutFlex.h
        Layout/LayoutFlex/FlexDirection.h
        Widgets/Progress/Progress.cpp
        Widgets/Progress/Progress.h
        WidgetsProps/Widget/ProgressProps.h
        Widgets/Slider/Slider.cpp
        Widgets/Slider/Slider.h
        WidgetsProps/Widget/SliderProps.h

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
        Widgets/Nop/Nop.cpp
        Widgets/Nop/Nop.h
        WidgetsProps/Widget/NopProps.h
        Render/Render.cpp
        Render/Render.h
        Core/Rect.h
        api.h
        Api/ApiWidget.h
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
