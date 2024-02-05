add_library(assimp INTERFACE)
target_include_directories(assimp INTERFACE ./)
target_link_libraries(assimp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/assimp-vc143-mt.lib)
add_target_dll(assimp ${CMAKE_CURRENT_SOURCE_DIR}/assimp-vc143-mt.dll)