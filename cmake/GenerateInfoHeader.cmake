include(${SOURCE_DIR}/cmake/Common.cmake)


git_info(GIT_HASH GIT_BRANCH)

message(STATUS "!! Running GenerateInfoHeader ${GIT_HASH} ${GIT_BRANCH}")

string(TIMESTAMP BUILD_TIME "%Y-%m-%d %H:%M:%S")

configure_file(
        "${INPUT_FILE}"
        "${OUTPUT_FILE}.tmp"
        @ONLY
)

execute_process(
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OUTPUT_FILE}.tmp"
        "${OUTPUT_FILE}"
)

file(REMOVE "${OUTPUT_FILE}.tmp")