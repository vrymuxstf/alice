file(GLOB_RECURSE SOURCE imgui/*.h imgui/*.cpp)

add_library(imgui INTERFACE)
target_sources(imgui INTERFACE ${SOURCE})
target_link_libraries(imgui INTERFACE glad glfw)
target_include_directories(imgui INTERFACE imgui)