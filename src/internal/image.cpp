#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include "image.hpp"

#include <format>
#include <map>
#include <stdexcept>

#include "../game/camera.hpp"

namespace image {
    std::map<std::string, SpriteSheet> loaded_sprite_sheets;

    /**
    * Load an image from a file.
    * @param path
    * @return An SDL_Surface created from the file.
    */
    SDL_Surface *LoadSurfaceFromImage(const std::string& path);
}

SDL_Surface *image::LoadSurfaceFromImage(const std::string &path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr)
        throw std::runtime_error(std::format("Failed to load image: {}.", path));

    return surface;
}

void image::LoadSpriteSheet(const std::string &tag, const std::string &path, const int tile_width, const int tile_height) {
    auto *renderer = internals::GetRenderer();
    auto *surface = LoadSurfaceFromImage(path);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    const SpriteSheet sprite_sheet {
        texture,
        tile_width,
        tile_height
    };

    if (loaded_sprite_sheets.contains(tag))
        throw std::runtime_error(std::format("Duplicate spritesheet tag \"{}\".", tag));

    loaded_sprite_sheets.try_emplace(tag, sprite_sheet);
}

const image::SpriteSheet &image::GetSpriteSheet(const std::string &tag) {
    if (!loaded_sprite_sheets.contains(tag))
        throw std::runtime_error(std::format("No spritesheet exists with tag \"{}\".", tag));

    return loaded_sprite_sheets.at(tag);
}

void image::RenderSprite(const Sprite &sprite, const Transform &transform, const SDL_RendererFlip flip) {
    const SDL_Rect src_rect {
        .x = sprite.sprite_sheet.tile_width * sprite.tile_x + sprite.padding,
        .y = sprite.sprite_sheet.tile_height * sprite.tile_y + sprite.padding,
        .w = sprite.sprite_sheet.tile_width - sprite.padding,
        .h = sprite.sprite_sheet.tile_height - sprite.padding
    };

    const Transform& camera_transform = camera::GetTransform();
    const SDL_FRect dst_rect {
        .x = transform.position.x - camera_transform.position.x,
        .y = transform.position.y - camera_transform.position.y,
        .w = transform.size.y,
        .h = transform.size.y
    };

    auto *renderer = internals::GetRenderer();
    SDL_RenderCopyExF(renderer, sprite.sprite_sheet.texture, &src_rect, &dst_rect, 0.0, nullptr, flip);
}
