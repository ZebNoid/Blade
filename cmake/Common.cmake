include_guard()


# set as unicode
function(with_unicode TARGET_NAME)
    # TODO only MSVC?
    if (MSVC)
        target_compile_definitions(
                ${TARGET_NAME}
                PRIVATE
                UNICODE
                _UNICODE
        )
    endif ()
endfunction()


# disable console
function(with_console TARGET_NAME ENABLE)
    if (ENABLE)
        set_target_properties(${TARGET_NAME}
                PROPERTIES
                WIN32_EXECUTABLE FALSE
        )

        message(STATUS "Console enabled for ${TARGET_NAME}")
    else ()
        set_target_properties(${TARGET_NAME}
                PROPERTIES
                WIN32_EXECUTABLE TRUE
        )
        if (MSVC)
            target_link_options(${TARGET_NAME}
                    PRIVATE
                    "/ENTRY:mainCRTStartup"
            )
        elseif (MINGW)
            target_link_options(${TARGET_NAME}
                    PRIVATE
                    -mwindows
            )
        endif ()
        message(STATUS "Console disabled for ${TARGET_NAME}")
    endif ()
endfunction()
