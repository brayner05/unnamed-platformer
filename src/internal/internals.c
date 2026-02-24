#include <SDL2/SDL_image.h>
#include "../internal/internals.h"
#include "image.h"

#define AXIS_MIN (INT16_MIN)
#define AXIS_MAX (INT16_MAX)

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

static int16_t Game_AxisTable[AXIS_COUNT] = { 0 };

extern void Game_KeyDownHandler(const SDL_Event *event) {
    const SDL_Keycode key = event->key.keysym.sym;
    switch (key) {
        case SDLK_w: {
            Game_AxisTable[AXIS_VERTICAL] = AXIS_MAX;
            break;
        }
        case SDLK_a: {
            Game_AxisTable[AXIS_HORIZONTAL] = AXIS_MIN;
            break;
        }
        case SDLK_s: {
            Game_AxisTable[AXIS_VERTICAL] = AXIS_MIN;
            break;
        }
        case SDLK_d: {
            Game_AxisTable[AXIS_HORIZONTAL] = AXIS_MAX;
            break;
        }
        case SDLK_SPACE: {
            Game_AxisTable[AXIS_JUMP] = AXIS_MAX;
            break;
        }
        default: break;
    }
}

extern void Game_KeyUpHandler(const SDL_Event *event) {
    const SDL_Keycode key = event->key.keysym.sym;
    switch (key) {
        case SDLK_w: {
            Game_AxisTable[AXIS_VERTICAL] = 0;
            break;
        }
        case SDLK_a: {
            Game_AxisTable[AXIS_HORIZONTAL] = 0;
            break;
        }
        case SDLK_s: {
            Game_AxisTable[AXIS_VERTICAL] = 0;
            break;
        }
        case SDLK_d: {
            Game_AxisTable[AXIS_HORIZONTAL] = 0;
            break;
        }
        case SDLK_SPACE: {
            Game_AxisTable[AXIS_JUMP] = 0;
            break;
        }
        default: break;
    }
}

extern int Game_GetAxis(Game_ControlAxis axis) {
    return (int) Game_AxisTable[axis];
}

extern Vector2D Game_GetWindowSize(void) {
    int width, height;
    SDL_GetWindowSize(Game_Internals.window, &width, &height);
    const Vector2D dimensions = {
        .x = (float) width,
        .y = (float) height
    };
    return dimensions;
}