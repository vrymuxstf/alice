add_library(alice-game-renderer INTERFACE)

file(GLOB_RECURSE SOURCE *.h *.cpp)

target_sources(alice-game-renderer INTERFACE ${SOURCE})

target_include_directories(alice-game-renderer INTERFACE ./)
target_link_libraries(alice-game-renderer INTERFACE alice-game-framework glad sdl imgui)