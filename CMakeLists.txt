cmake_minimum_required(VERSION 3.26)
project(alice)

set(CMAKE_CXX_STANDARD 23)

include(cmake/alice.cmake)

add_subdirectory(sources)
add_subdirectory(programs)