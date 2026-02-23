#include <SDL2/SDL_image.h>
#include "image.h"

#define GAME_TILEMAPS_MAX 32
static struct {
    Game_TileMap tilemaps[GAME_TILEMAPS_MAX];
    size_t count;
} Game_TileMapManager;

extern SDL_Surface *Game_LoadImage(const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (surface == NULL) {
        Game_ThrowError("Failed to load image");
        return NULL;
    }
    return surface;
}

extern int Game_InitTileMaps(void) {
    Game_TileMapManager.count = 0;
    return 0;
}

extern int Game_LoadTilemap(const char *path, int tile_width, int tile_height) {
    if (Game_TileMapManager.count == GAME_TILEMAPS_MAX) {
        Game_ThrowError("MAX TILEMAPS EXCEEDED");
        return -1;
    }

    SDL_Surface *surface = Game_LoadImage(path);
    const Game_TileMap tilemap = {
        .surface = surface,
        .tile_width = tile_width,
        .tile_height = tile_height,
    };

    Game_TileMapManager.tilemaps[Game_TileMapManager.count++] = tilemap;
    return 0;
}

extern Game_TileMap *Game_GetTileMap(size_t id) {
    if (id >= Game_TileMapManager.count) {
        Game_ThrowError("Tilemap access outside of bounds");
        return NULL;
    }
    return &Game_TileMapManager.tilemaps[id];
}

extern void Game_RenderTiledImage(Game_TiledImage *image, Transform *transform) {
    const SDL_Rect src_rect = {
        .x = image->tilemap->tile_width * image->tile_x,
        .y = image->tilemap->tile_height * image->tile_y,
        .w = image->tilemap->tile_width,
        .h = image->tilemap->tile_height
    };

    const SDL_FRect dst_rect = {
        .x = transform->position.x,
        .y = transform->position.y,
        .w = transform->size.x,
        .h = transform->size.y
    };

    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_Texture *tilemap_texture = SDL_CreateTextureFromSurface(renderer, image->tilemap->surface);
    SDL_RenderCopyF(renderer, tilemap_texture, &src_rect, &dst_rect);
}
