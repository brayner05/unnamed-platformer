#include "main_loop.h"

#include "../internal/image.h"
#include "../internal/internals.h"

static SDL_Surface *image = NULL;

static void ProcessEvents(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            Game_Quit();
        }
    }
}

static void Update(void) {

}

static void Render(void) {
    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);

    SDL_RenderClear(renderer);

    // DELETE
    Transform t = {
        .position = {
            .x = 400,
            .y = 300
        },
        .size = {
            .x = 100,
            .y = 100
        }
    };

    Game_RenderImage(image, &t);
    // END

    SDL_RenderPresent(renderer);
}

extern void Game_MainLoop(void) {
    // DELETE
    image = Game_LoadImage("../assets/png/test_image.png");
    if (image == NULL) {
        fprintf(stderr, "Error: %s\n", Game_GetError());
        return;
    }
    // END

    while (Game_IsRunning()) {
        ProcessEvents();
        Update();
        Render();
        SDL_Delay(15);
    }
}