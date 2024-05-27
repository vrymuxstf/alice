add_library(sdl INTERFACE)
target_include_directories(sdl INTERFACE include)
target_link_libraries(sdl INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/SDL3.lib)

alice_link_dlls(sdl ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/SDL3.dll)