#include "main_loop.h"

#include "../entity/player.h"
#include "../internal/image.h"
#include "../internal/internals.h"

#define METER_FACTOR 128

static void ProcessEvents(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Game_Quit();
        }
    }
}

static void Start() {
    Game_TiledImage knight = {
        .tilemap = Game_GetTileMap(GAME_TILEMAP_KNIGHT),
        .tile_x = 0,
        .tile_y = 0
    };
    Player_Init(&knight);
}

static void Update(void) {}

static void Render(void) {
    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);

    SDL_RenderClear(renderer);
    Player_Render();
    SDL_RenderPresent(renderer);
}

extern void Game_MainLoop(void) {
    Start();
    while (Game_IsRunning()) {
        ProcessEvents();
        Update();
        Render();
        SDL_Delay(200);
    }
}