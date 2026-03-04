cmake_minimum_required(VERSION 4.1)
project(unnamed_game C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.c
)

add_executable(unnamed_game
        src/main.cpp
        src/internal/internals.hpp
        src/internal/internals.cpp
        src/internal/image.hpp
        src/internal/image.cpp
        src/game/camera.hpp
        src/game/camera.cpp
        src/game/main_loop.hpp
        src/game/main_loop.cpp
        ${SOURCES}
        src/game/camera.cpp
        src/game/camera.hpp
        src/internal/input.cpp
        src/internal/input.hpp)

target_link_libraries(unnamed_game SDL2 SDL2main SDL2_ttf SDL2_image)
