#include <cstdio>
#include <stdexcept>
#include <format>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "internal/internals.hpp"
#include "game/main_loop.hpp"
#include "internal/image.hpp"

/**
 * The main purpose of this struct is to make initializing and quitting SDL
 * easy enough that it's not necessary to worry about quitting every time
 * something goes wrong. This is accomplished by automatically quitting SDL
 * as soon as the instance goes out of scope.
 */
struct SdlInstance {
    explicit SdlInstance(const Uint32 flags) {
        if (SDL_Init(flags) < 0)
            throw std::runtime_error("Failed to initialize SDL2.");

        if (IMG_Init(IMG_INIT_PNG) < 0)
            throw std::runtime_error("Failed to initialize SDL2_image.");
    }

    ~SdlInstance() {
        IMG_Quit();
        SDL_Quit();
    }
};

int main() {
    auto sdl_instance = SdlInstance(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        "GAME",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);

    if (window == nullptr)
        throw std::runtime_error(std::format("Error: Failed to create window: {}", SDL_GetError()));

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
        throw std::runtime_error(std::format("Error: Failed to create renderer: {}", SDL_GetError()));

    internals::Init(window, renderer);

    Game_LoadTilemap(GAME_TILEMAP_KNIGHT, "../assets/png/knight.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_SLIME_GREEN, "../assets/png/slime_green.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_SLIME_PURPLE, "../assets/png/slime_purple.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_WORLD, "../assets/png/world_tileset.png", 16, 16);
    Game_MainLoop();

    for (int id = 0; id < GAME_TILEMAPS_MAX; ++id) {
        Game_DestroyTileMap(static_cast<Game_TileMapId>(id));
    }

    if (window != nullptr)     SDL_DestroyWindow(window);
    if (renderer != nullptr)   SDL_DestroyRenderer(renderer);
}
