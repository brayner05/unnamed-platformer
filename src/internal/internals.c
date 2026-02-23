#include <SDL2/SDL_image.h>
#include "../internal/internals.h"

static struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    char *error_message;
    bool running;
} Game_Internals = {
    .window = NULL,
    .renderer = NULL,
    .error_message = NULL,
    .running = false,
};

extern int Game_Init(SDL_Window *window, SDL_Renderer *renderer) {
    if (window == NULL || renderer == NULL)
        return GAME_INIT_FAIL;

    Game_Internals.window = window;
    Game_Internals.renderer = renderer;
    Game_Internals.running = true;

    return GAME_INIT_OK;
}

extern bool Game_IsRunning(void) {
    return Game_Internals.running;
}

extern void Game_Quit(void) {
    Game_Internals.running = false;
}

extern SDL_Window *Game_GetWindow(void) {
    return Game_Internals.window;
}

extern SDL_Renderer *Game_GetRenderer(void) {
    return Game_Internals.renderer;
}

extern void Game_ThrowError(const char *message) {
    if (message != NULL) {
        Game_Internals.error_message = (char *) message;
    }
}

extern const char *Game_GetError(void) {
    return Game_Internals.error_message;
}