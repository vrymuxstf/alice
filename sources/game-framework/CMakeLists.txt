add_library(alice-game-framework INTERFACE
        ../core/alice/core/app.h)
target_sources(alice-game-framework INTERFACE camera.h space.h)
target_include_directories(alice-game-framework INTERFACE glm-1.0.1-light)