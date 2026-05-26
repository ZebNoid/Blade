project(Api)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} INTERFACE
        Api/ApiWidget.h
        Api/ApiBackend.h

        Common/Types.h
        Common/Thickness.h
        Common/LayoutProps.h
        Common/Rect.h
        Common/Size.h
        Common/Point.h
        Common/Property.h
        Common/Callbacks.h
        Common/Props.h
        Common/Logger.h

        Events/Events.h
        Events/EventPayload.h
        Events/EventResult.h
        Events/BackendEvent.h

        Api/BackendCommand.h
        Api/CommandType.h
        Common/Props.h
)

# use Unicode
#with_unicode(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
