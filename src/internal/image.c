#include <SDL2/SDL_image.h>
#include "image.h"

// PARAM: position Vector2
extern void Game_RenderImage(SDL_Surface *image, Transform *transform) {
    SDL_Renderer *renderer = Game_GetRenderer();

    const SDL_Rect src_rect = {
        .x = 0,
        .y = 0,
        .w = image->w,
        .h = image->h
    };

    const SDL_FRect dst_rect = {
        .x = transform->position.x,
        .y = transform->position.y,
        .w = transform->size.x,
        .h = transform->size.y
    };

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopyF(renderer, texture, &src_rect, &dst_rect);
}

extern SDL_Surface *Game_LoadImage(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        Game_ThrowError("Failed to load image");
        return NULL;
    }
    return surface;
}
