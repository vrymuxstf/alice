cmake_minimum_required(VERSION 3.26)
project(alice)

set(CMAKE_CXX_STANDARD 23)

include(cmake/alice.cmake)

add_subdirectory(modules/core)
add_subdirectory(modules/program)

add_subdirectory(projects/code)
add_subdirectory(projects/nightmares)