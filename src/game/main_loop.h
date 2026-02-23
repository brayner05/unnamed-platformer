#ifndef UNNAMED_GAME_MAIN_LOOP_H
#define UNNAMED_GAME_MAIN_LOOP_H
#include <SDL2/SDL.h>

/**
 * Runs the game by creating an infinite loop which
 * processes events, updates game state, and renders the next frame.
 */
extern void Game_MainLoop(void);

#endif //UNNAMED_GAME_MAIN_LOOP_H