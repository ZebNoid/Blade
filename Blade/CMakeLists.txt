project(Blade VERSION 0.1.6)

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
        Backend/NativeWindow/NativeWindow.cpp
        Backend/NativeWindow/NativeWindow.h
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
        Props/Common/Alignment.h
        Props/Widget/ColumnProps.h
        Props/Widget/LabelProps.h
        Props/Window/WindowProps.h
        Props/Common/Size.h
        Props/Common/Thickness.h
        Windows/WindowBuilder/WindowBuilder.cpp
        Windows/WindowBuilder/WindowBuilder.h
        Props/Common/Point.h
        Props/Common/TextAlign.h
        Props/Widget/ButtonProps.h
        Props/Common/StyleProps.h
        Backend/NativeCheckbox/NativeCheckbox.cpp
        Backend/NativeCheckbox/NativeCheckbox.h
        Widgets/Checkbox/Checkbox.cpp
        Widgets/Checkbox/Checkbox.h
        Props/Widget/CheckboxProps.h
        Backend/NativeRadioButton/NativeRadioButton.cpp
        Backend/NativeRadioButton/NativeRadioButton.h
        Widgets/RadioButton/RadioButton.cpp
        Widgets/RadioButton/RadioButton.h
        Props/Widget/RadioButtonProps.h
        Props/Widget/TextFieldProps.h
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
)

# TODO remove?
target_precompile_headers(${PROJECT_NAME}
        PRIVATE
        pch.h
)

# TODO fix include
#target_compile_options(Blade PRIVATE /W4)
