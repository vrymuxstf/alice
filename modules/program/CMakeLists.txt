add_library(alice-program INTERFACE)

file(GLOB_RECURSE SOURCE include/*.h src/*.cpp)
target_sources(alice-program INTERFACE ${SOURCE})

target_include_directories(alice-program INTERFACE include)