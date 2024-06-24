alice_add_program(alice-code ${SOURCE})

file(GLOB_RECURSE SOURCE *.h *.cpp)
target_sources(alice-core PUBLIC ${SOURCE})

target_link_libraries(alice-code sdl alice-core alice-game-renderer alice-game-framework)

alice_copy_dlls(alice-code)