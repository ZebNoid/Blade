cmake_minimum_required(VERSION 3.21)
project(BladeFramework VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Common.cmake)

add_subdirectory(Api)
add_subdirectory(Backend)
add_subdirectory(Blade)
add_subdirectory(Example)
