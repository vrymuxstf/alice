add_library(glfw INTERFACE)
target_include_directories(glfw INTERFACE include)
target_link_directories(glfw INTERFACE lib-vc2022)
target_link_libraries(glfw INTERFACE glfw3)