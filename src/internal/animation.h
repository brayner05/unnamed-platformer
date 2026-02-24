#ifndef UNNAMED_GAME_ANIMATION_H
#define UNNAMED_GAME_ANIMATION_H
#include <SDL2/SDL_timer.h>
/**
 * Play an animation. An animation should be in the form:
 * ```
 * void [Name]Animation(void) {...}
 * ```
 * The animation will change frames roughly every `speed_ms` milliseconds.
 * @param Animation
 * @param ms_per_frame
 */
extern void Game_PlayAnimation(void (*Animation)(void), Uint32 ms_per_frame);

#endif //UNNAMED_GAME_ANIMATION_H