#include "main_loop.h"

#include "../entity/player.h"
#include "../internal/image.h"
#include "../internal/internals.h"

#define METER_FACTOR 128

static void ProcessEvents(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            Game_Quit();

        if (event.type == SDL_KEYDOWN)
            Game_KeyDownHandler(&event);

        if (event.type == SDL_KEYUP)
            Game_KeyUpHandler(&event);
    }
}

static void Start() {
    Player_Init();
}

static void Update(void) {
    Player_Update();
}

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
        SDL_Delay(120);
    }
}