#include <map>
#include "input.hpp"

#define AXIS_MIN (INT16_MIN)
#define AXIS_MAX (INT16_MAX)

namespace input {
    std::map<Axis, int16_t> axis_table {};
}

void input::KeyDownHandler(const SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_w: {
            axis_table[Axis::Vertical] = AXIS_MAX;
            break;
        }
        case SDLK_a: {
            axis_table[Axis::Horizontal] = AXIS_MIN;
            break;
        }
        case SDLK_s: {
            axis_table[Axis::Vertical] = AXIS_MIN;
            break;
        }
        case SDLK_d: {
            axis_table[Axis::Horizontal] = AXIS_MAX;
            break;
        }
        case SDLK_SPACE: {
            axis_table[Axis::Jump] = AXIS_MAX;
            break;
        }
        default: break;
    }
}

void input::KeyUpHandler(const SDL_Event &event) {
    switch (event.key.keysym.sym) {
        case SDLK_w: {
            axis_table[Axis::Vertical] = 0;
            break;
        }
        case SDLK_a: {
            axis_table[Axis::Horizontal] = 0;
            break;
        }
        case SDLK_s: {
            axis_table[Axis::Vertical] = 0;
            break;
        }
        case SDLK_d: {
            axis_table[Axis::Horizontal] = 0;
            break;
        }
        case SDLK_SPACE: {
            axis_table[Axis::Jump] = 0;
            break;
        }
        default: break;
    }
}

void input::MouseDownHandler(const SDL_Event &event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT: {
            axis_table[Axis::MouseLeft] = AXIS_MAX;
            break;
        }
        case SDL_BUTTON_RIGHT: {
            axis_table[Axis::MouseRight] = AXIS_MAX;
            break;
        }
        default: break;
    }
}
void input::MouseUpHandler(const SDL_Event &event) {
    switch (event.button.button) {
        case SDL_BUTTON_LEFT: {
            axis_table[Axis::MouseLeft] = 0;
            break;
        }
        case SDL_BUTTON_RIGHT: {
            axis_table[Axis::MouseRight] = 0;
            break;
        }
        default: break;
    }
}

float input::GetAxis(const Axis axis) {
    const auto axis_value_raw = axis_table[axis];
    const auto axis_value = static_cast<float>(axis_value_raw) / INT16_MAX;
    return axis_value;
}