#include <SDL2/SDL_timer.h>
#include "animation.h"

#include "internals.h"

extern void Game_PlayAnimation(void (*Animation)(void), const Uint32 ms_per_frame) {
    static Uint32 time_last_frame = 0;

    const Uint32 time_now = SDL_GetTicks();
    if (time_now - time_last_frame < ms_per_frame) {
        return;
    }

    Animation();
    time_last_frame = SDL_GetTicks();
}
