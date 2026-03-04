#ifndef UNNAMED_GAME_GAME_INTERNALS_H
#define UNNAMED_GAME_GAME_INTERNALS_H
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "../math/vector.h"

#define TARGET_FPS 60.0f
#define TARGET_FRAME_TIME_MS (1000.0f / TARGET_FPS)
#define METER_FACTOR (64)

namespace internals {
    /**
     * Initialize the game by passing the game dependencies.
     * @param window The window to be used by the game.
     * @param renderer The renderer to be used by the game.
     */
    void Init(SDL_Window *window, SDL_Renderer *renderer);

    /**
     * Signals the game to quit. NOTE: this function does not
     * free any memory, or release anything.
     * It only sets `Game_Internals.running` to `false`.
     */
    void Quit();

    /**
    * @return Whether the game is currently running or not.
    */
    bool IsRunning();

    /**
     * @return A pointer to the main game window.
     */
    SDL_Window *GetWindow();

    /**
     * @return A pointer to the main game renderer.
     */
    SDL_Renderer *GetRenderer();

    /**
     * *NOTE* The width and height returned by this method are floats
     * due to the current limitations of the <code>Vector2D</code> struct (i.e. it uses
     * structs). It is recommended to cast the values to <code>int</code> before using them.
     *
     * @return The dimensions of the window.
     */
    Vector2D GetWindowSize();
}

#endif