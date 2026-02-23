cmake_minimum_required(VERSION 4.1)
project(unnamed_game C)

set(CMAKE_C_STANDARD 11)

add_executable(unnamed_game src/main.c
        src/internal/internals.c
        src/internal/internals.h
        src/game/main_loop.c
        src/game/main_loop.h
        src/internal/image.c
        src/internal/image.h
        src/math/vector.h
        src/math/transform.h
        src/entity/player.c
        src/entity/player.h)

target_link_libraries(unnamed_game SDL2 SDL2main SDL2_ttf SDL2_image)
