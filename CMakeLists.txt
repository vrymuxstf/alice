cmake_minimum_required(VERSION 3.26)
project(alice)

set(CMAKE_CXX_STANDARD 23)

include(cmake/alice.cmake)

add_subdirectory(src/assimp)
add_subdirectory(src/glad)
add_subdirectory(src/glfw-3.3.8)
add_subdirectory(src/glm)
add_subdirectory(src/imgui)
add_subdirectory(src/renderer)