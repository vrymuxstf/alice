add_library(alice-core INTERFACE)

file(GLOB_RECURSE SOURCE include/*.h src/*.cpp)
target_sources(alice-core INTERFACE ${SOURCE})

target_include_directories(alice-core INTERFACE include)