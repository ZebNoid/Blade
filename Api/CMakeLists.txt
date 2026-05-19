project(Api)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_library(${PROJECT_NAME} INTERFACE
        ApiWidget.h
        ApiBackend.h
        Common/Rect.h
        Common/CommonTypes.h
        Common/Size.h
        Common/Point.h
        Common/Common.h
)

# use Unicode
#with_unicode(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)