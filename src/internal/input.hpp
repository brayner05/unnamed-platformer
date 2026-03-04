#ifndef UNNAMED_GAME_INPUT_HPP
#define UNNAMED_GAME_INPUT_HPP

#include <SDL2/SDL_events.h>

namespace input {
    enum class Axis {
        Horizontal,
        Vertical,
        Jump,
        MouseLeft,
        MouseRight
    };
    float GetAxis(Axis axis);
    void KeyDownHandler(const SDL_Event& event);
    void KeyUpHandler(const SDL_Event& event);
    void MouseDownHandler(const SDL_Event& event);
    void MouseUpHandler(const SDL_Event& event);
}

#endif //UNNAMED_GAME_INPUT_HPP