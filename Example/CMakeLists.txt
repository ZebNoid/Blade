project(Example)

# Use the names to logic check
if (NOT PROJECT_IS_TOP_LEVEL)
    message(STATUS "Building ${PROJECT_NAME} as part of ${CMAKE_PROJECT_NAME}")
endif ()

add_executable(${PROJECT_NAME}
        main.cpp
        Resource/App.manifest
        Resource/App.rc
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Blade
)

#target_precompile_headers(${PROJECT_NAME}
#        PRIVATE
#        pch.h
#)

# use Unicode
with_unicode(${PROJECT_NAME})
# Hide console window
#with_console(${PROJECT_NAME} FALSE)
with_console(${PROJECT_NAME} TRUE)

