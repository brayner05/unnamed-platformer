#include "main_loop.h"

#include "camera.h"
#include "../internal/image.h"
#include "./entity/player/player.h"
#include "../internal/internals.h"
#include "physics/physics.h"

// TEMPORARY START
// TEMPORARY END

/**
 * Poll and process SDL events whenever available.
 */
static void ProcessEvents(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            Game_Quit();

        if (event.type == SDL_KEYDOWN)
            Game_KeyDownHandler(&event);

        if (event.type == SDL_KEYUP)
            Game_KeyUpHandler(&event);

        if (event.type == SDL_MOUSEBUTTONDOWN)
            Game_MouseDownHandler(&event);

        if (event.type == SDL_MOUSEBUTTONUP)
            Game_MouseUpHandler(&event);
    }
}

/**
 * Run before the gameloop begins.
 */
static void Start() {
    Physics_EnableCollision();
    Camera_Init();
    Player_Init();
}

/**
 * Updates game state once per frame.
 */
static void Update(void) {
    Player_Update();
}

/**
 * Deals with rendering graphics once per frame.
 */
static void Render(void) {
    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);

    SDL_RenderClear(renderer);
    Player_Render();
    Game_TiledSprite sp = {
        .tilemap = Game_GetTileMap(GAME_TILEMAP_WORLD),
        .tile_x = 1,
        .tile_y = 0
    };
    Transform transform = {
        .position = { 0, 0 },
        .size = { METER_FACTOR, METER_FACTOR }
    };
    Game_RenderTiledImage(&sp, &transform, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

/**
 * The actual game loop:
 */
extern void Game_MainLoop(void) {
    Start();
    while (Game_IsRunning()) {
        const Uint32 frame_start = SDL_GetTicks();

        ProcessEvents();
        Update();
        Render();

        const Uint32 frame_end = SDL_GetTicks();
        const Uint32 frame_time = frame_end - frame_start;

        /*
         * Cap the framerate at `TARGET_FRAME_TIME`.
         */
        if ((float) frame_time < TARGET_FRAME_TIME_MS) {
            const int delay_time = (int) (TARGET_FRAME_TIME_MS - (float) frame_time);
            SDL_Delay(delay_time);
        }
    }
}