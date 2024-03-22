add_library(alice-game-socket INTERFACE)

file(GLOB_RECURSE SOURCE include/*.h src/*.cpp)
target_sources(alice-game-socket INTERFACE ${SOURCE})

target_include_directories(alice-game-socket INTERFACE include)