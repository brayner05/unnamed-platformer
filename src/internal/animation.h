#ifndef UNNAMED_GAME_ANIMATION_H
#define UNNAMED_GAME_ANIMATION_H

#define Animation_Play(name, speed_ms) Game_PlayAnimation(Game_Animations_name##, speed_ms)
#define Animation_Create(name) static void Game_Animations_name##(void)

/**
 * Play an animation. An animation should be in the form:
 * ```
 * void [Name]Animation(void) {...}
 * ```
 * The animation will change frames roughly every `speed_ms` milliseconds.
 * @param Animation
 * @param speed_ms
 */
extern void Game_PlayAnimation(void (*Animation)(void), Uint32 speed_ms);

#endif //UNNAMED_GAME_ANIMATION_H