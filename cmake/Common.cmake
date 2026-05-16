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


# Project info.h
function(with_info_header TARGET_NAME)
    git_info(GIT_HASH GIT_BRANCH)

    message(STATUS "Generating ${FILE_NAME}.h for ${TARGET_NAME}")
    configure_file("${CMAKE_SOURCE_DIR}/cmake/${FILE_NAME}.h.in" "${PROJECT_SOURCE_DIR}/${FILE_NAME}.h" @ONLY)
    target_include_directories(${TARGET_NAME} PUBLIC
            "${PROJECT_BINARY_DIR}/gen/"
    )
endfunction()


# Git info
function(git_info output_hash output_branch)
    find_package(Git QUIET)

    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${SOURCE_DIR} # CMAKE_CURRENT_LIST_DIR
            OUTPUT_VARIABLE GIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
            WORKING_DIRECTORY ${SOURCE_DIR} # CMAKE_CURRENT_LIST_DIR
            OUTPUT_VARIABLE GIT_BRANCH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    set(${output_hash} "${GIT_HASH}" PARENT_SCOPE)
    set(${output_branch} "${GIT_BRANCH}" PARENT_SCOPE)
    # message(STATUS "Git Commit Info\n\tHash: ${GIT_HASH}\n\tBranch: ${GIT_BRANCH}")
endfunction()


function(with_info_header TARGET_NAME)

    set(INFO_HEADER_DIR
            "${CMAKE_CURRENT_BINARY_DIR}/generated"
    )

    set(INFO_HEADER
            "${INFO_HEADER_DIR}/info.h"
    )

    file(MAKE_DIRECTORY ${INFO_HEADER_DIR})

    add_custom_command(
            OUTPUT ${INFO_HEADER}

            COMMAND ${CMAKE_COMMAND}
            -DINPUT_FILE=${CMAKE_SOURCE_DIR}/cmake/info.h.in
            -DOUTPUT_FILE=${INFO_HEADER}
            -DSOURCE_DIR=${CMAKE_SOURCE_DIR}
            -DPROJECT_VERSION=${PROJECT_VERSION}
            -P ${CMAKE_SOURCE_DIR}/cmake/GenerateInfoHeader.cmake

            DEPENDS
            ${CMAKE_SOURCE_DIR}/cmake/info.h.in

            COMMENT "Generating info.h"

            VERBATIM
    )

    add_custom_target(
            ${TARGET_NAME}_info_header
            DEPENDS ${INFO_HEADER}
    )

    add_dependencies(
            ${TARGET_NAME}
            ${TARGET_NAME}_info_header
    )

    target_include_directories(
            ${TARGET_NAME}
            PRIVATE
            ${INFO_HEADER_DIR}
    )

endfunction()