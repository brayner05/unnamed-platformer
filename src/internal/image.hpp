#ifndef UNNAMED_GAME_IMAGE_H
#define UNNAMED_GAME_IMAGE_H

#include <string>
#include "internals.hpp"
#include "../math/transform.h"

#define GAME_TILEMAPS_MAX 32

namespace image {
    struct SpriteSheet {
        SDL_Texture *texture;
        int tile_width;
        int tile_height;

        SpriteSheet(SDL_Texture *texture, const int tile_width, const int tile_height)
            : texture(texture), tile_width(tile_width), tile_height(tile_height) {}
    };

    struct Sprite {
        const SpriteSheet& sprite_sheet;
        int tile_x;
        int tile_y;
        int padding;

        Sprite(const SpriteSheet& sprite_sheet, const int tile_x, const int tile_y, const int padding)
            : sprite_sheet(sprite_sheet), tile_x(tile_x), tile_y(tile_y), padding(padding) {}
    };

    void LoadSpriteSheet(const std::string& tag, const std::string& path, int tile_width, int tile_height);

    const SpriteSheet& GetSpriteSheet(const std::string& tag);

    /**
     * Render a texture directly from a tilemap without needing to load
     * that texture specifically.
     * @param sprite
     * @param transform
     * @param flip
     */
    void RenderSprite(const Sprite& sprite, const Transform& transform, const SDL_RendererFlip flip);
}

#endif //UNNAMED_GAME_IMAGE_H