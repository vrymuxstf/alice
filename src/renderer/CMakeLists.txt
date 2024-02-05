file(GLOB_RECURSE SOURCE *.h *.cpp)

add_library(renderer INTERFACE)
target_sources(renderer INTERFACE ${SOURCE})
target_include_directories(renderer INTERFACE .)
target_link_libraries(renderer INTERFACE glfw assimp)

add_executable(renderer_opengl)
target_link_libraries(renderer_opengl renderer glad imgui_gl)
target_compile_definitions(renderer_opengl PRIVATE OPENGL)

collect_dlls(renderer_opengl)

find_package(Vulkan REQUIRED)

add_executable(renderer_vulkan)
target_link_libraries(renderer_vulkan renderer Vulkan::Vulkan imgui_vk)
target_compile_definitions(renderer_vulkan PRIVATE VULKAN)