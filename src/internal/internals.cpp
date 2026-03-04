#include <stdexcept>
#include "../internal/internals.hpp"
#include "image.hpp"

namespace internals {
    static SDL_Window *window { nullptr };
    static SDL_Renderer *renderer { nullptr };
    static bool running { false };
}

void internals::Init(SDL_Window *window, SDL_Renderer *renderer) {
    if (window == nullptr)
        throw std::runtime_error("Cannot initialize game if window is null.");

    if (renderer == nullptr)
        throw std::runtime_error("Cannot initialize game if renderer is null.");

    internals::window = window;
    internals::renderer = renderer;
}

bool internals::IsRunning() {
    return running;
}

void internals::Quit() {
    running = false;
}

SDL_Window *internals::GetWindow() {
    return window;
}

SDL_Renderer *internals::GetRenderer() {
    return renderer;
}

Vector2D internals::GetWindowSize() {
    int width, height;
    SDL_GetWindowSize(internals::window, &width, &height);
    const Vector2D dimensions = {
        .x = static_cast<float>(width),
        .y = static_cast<float>(height)
    };
    return dimensions;
}
