#ifndef UNNAMED_GAME_GAME_INTERNALS_H
#define UNNAMED_GAME_GAME_INTERNALS_H
#include <stdbool.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_events.h>
#include "../math/vector.h"

#define TARGET_FPS 60.0f
#define TARGET_FRAME_TIME (1000.0f / TARGET_FPS)

#define METER_FACTOR 128

enum {
    GAME_INIT_FAIL  = -1,
    GAME_INIT_OK    = 0
};

typedef enum {
    AXIS_HORIZONTAL = 0,
    AXIS_VERTICAL,
    AXIS_JUMP,
    AXIS_COUNT
} Game_ControlAxis;

/**
 * Initialize the game by passing the game dependencies.
 * @param window The window to be used by the game.
 * @param renderer The renderer to be used by the game.
 * @return 0 on success, -1 on error.
 */
extern int Game_Init(SDL_Window *window, SDL_Renderer *renderer);

/**
 * Signals the game to quit. NOTE: this function does not
 * free any memory, or release anything.
 * It only sets `Game_Internals.running` to `false`.
 */
extern void Game_Quit(void);

/**
 * @return Whether the game is currently running or not.
 */
extern bool Game_IsRunning(void);

/**
 * @return A pointer to the main game window.
 */
extern SDL_Window *Game_GetWindow(void);

/**
 * @return A pointer to the main game renderer.
 */
extern SDL_Renderer *Game_GetRenderer(void);

/**
 * @return The last error message or `"UNKNOWN_ERROR"` if there is
 * no previous error message.
 */
extern const char *Game_GetError(void);

/**
 * @param message
 */
extern void Game_ThrowError(const char *message);

extern void Game_KeyDownHandler(const SDL_Event *event);

extern void Game_KeyUpHandler(const SDL_Event *event);

extern int Game_GetAxis(Game_ControlAxis axis);

/**
 * *NOTE* The width and height returned by this method are floats
 * due to the current limitations of the <code>Vector2D</code> struct (i.e. it uses
 * structs). It is recommended to cast the values to <code>int</code> before using them.
 *
 * @return The dimensions of the window.
 */
extern Vector2D Game_GetWindowSize(void);

#endif