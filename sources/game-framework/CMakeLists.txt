add_library(alice-game-framework INTERFACE)

file(GLOB_RECURSE SOURCE *.h *.hpp *.cpp)
target_sources(alice-game-framework INTERFACE ${SOURCE})

target_include_directories(alice-game-framework INTERFACE . glm-1.0.1-light)

target_link_libraries(alice-game-framework INTERFACE)