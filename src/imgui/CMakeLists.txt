file(GLOB SOURCE *.h *.cpp)

add_library(imgui INTERFACE)
target_sources(imgui INTERFACE ${SOURCE})
target_link_libraries(imgui INTERFACE glfw)
target_include_directories(imgui INTERFACE .)

add_library(imgui_gl INTERFACE)
target_sources(imgui_gl INTERFACE opengl/imgui_impl_opengl3.h opengl/imgui_impl_opengl3.cpp)
target_link_libraries(imgui_gl INTERFACE imgui)

add_library(imgui_vk INTERFACE)
target_sources(imgui_vk INTERFACE vulkan/imgui_impl_vulkan.h vulkan/imgui_impl_vulkan.cpp)
target_link_libraries(imgui_vk INTERFACE imgui)