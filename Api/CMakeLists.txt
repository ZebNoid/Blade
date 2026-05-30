project(Api)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} INTERFACE
        Api/ApiBackend.h
        Command/AppCommand.h
        Command/AppCommandType.h
        Command/ElementCommand.h
        Command/ElementCommandType.h
        Message/BackendMessage.h
        Message/BackendMessageType.h
        Menu/MenuData.h
        Menu/MenuTrigger.h
        Menu/Shortcut.h
        Geometry/Point.h
        Geometry/Size.h
        Geometry/Rect.h
        Geometry/Thickness.h
        Style/Color.h
        Logging/Logger.h
        Callback/Callbacks.h
        Lifecycle/Lifetime.h
        Render/RenderCommand.h
        Render/RenderCommandType.h
        Render/RenderOp.h
        Fabric/WindowPlacement.h
        Widget/WidgetType.h
        Widget/ComponentType.h
        Window/CaptionProps.h
        Window/WindowPlacementProps.h
        Window/WindowState.h

        Common/Types.h
        Common/Modifier.h
        Common/LayoutProps.h
        Common/Property.h
        Common/Props.h

        Events/Events.h
        Events/EventContext.h
        Events/EventPayload.h
        Events/EventResult.h
        Events/BackendEvent.h

        Common/Props.h
)

# use Unicode
#with_unicode(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
