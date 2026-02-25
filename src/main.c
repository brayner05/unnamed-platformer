#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

#include "internal/internals.h"
#include "game/main_loop.h"
#include "internal/image.h"

int main(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        fprintf(stderr, "Error: %s\n", IMG_GetError());
        goto cleanup_no_img;
    }

    SDL_Window *window = SDL_CreateWindow(
        "GAME",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr,"Error: Failed to create window [%s]\n", SDL_GetError());
        goto cleanup;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        fprintf(stderr, "Error: Failed to create renderer [%s]\n", SDL_GetError());
        goto cleanup;
    }

    if (Game_Init(window, renderer) < 0) {
        fprintf(stderr, "Error: Failed to initialize game [%s]\n", Game_GetError());
        goto cleanup;
    }

    Game_LoadTilemap(GAME_TILEMAP_KNIGHT, "../assets/png/knight.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_SLIME_GREEN, "../assets/png/slime_green.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_SLIME_PURPLE, "../assets/png/slime_purple.png", 32, 32);
    Game_LoadTilemap(GAME_TILEMAP_WORLD, "../assets/png/world_tileset.png", 16, 16);
    Game_MainLoop();

    for (size_t id = 0; id < GAME_TILEMAPS_MAX; ++id) {
        Game_DestroyTileMap(id);
    }

cleanup:
    IMG_Quit();
cleanup_no_img:
    if (window != NULL)     SDL_DestroyWindow(window);
    if (renderer != NULL)   SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
