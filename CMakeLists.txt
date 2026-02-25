cmake_minimum_required(VERSION 4.1)
project(unnamed_game C)

set(CMAKE_C_STANDARD 11)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.c
)

add_executable(unnamed_game ${SOURCES})

target_link_libraries(unnamed_game SDL2 SDL2main SDL2_ttf SDL2_image)
