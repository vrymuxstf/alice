add_library(imgui INTERFACE)

file(GLOB_RECURSE SOURCE *.h *.cpp)

target_sources(imgui INTERFACE ${SOURCE})
target_include_directories(imgui INTERFACE ./)