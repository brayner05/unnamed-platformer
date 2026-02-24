#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include "image.h"

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

extern int Game_DestroyTileMap(size_t id) {
    if (id >= GAME_TILEMAPS_MAX) {
        Game_ThrowError("TILEMAP OUT OF BOUNDS");
        return -1;
    }

    Game_TileMap *tilemap = &Game_TileMapManager.tilemaps[id];
    SDL_DestroyTexture(tilemap->texture);
    tilemap->texture = NULL;

    return 0;
}

extern int Game_LoadTilemap(size_t id, const char *path, int tile_width, int tile_height) {
    if (id >= GAME_TILEMAPS_MAX) {
        Game_ThrowError("TILEMAP OUT OF BOUNDS");
        return -1;
    }

    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_Surface *surface = Game_LoadImage(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    const Game_TileMap tilemap = {
        .texture = texture,
        .tile_width = tile_width,
        .tile_height = tile_height,
    };

    Game_TileMapManager.tilemaps[id] = tilemap;
    return 0;
}

extern Game_TileMap *Game_GetTileMap(size_t id) {
    if (id >= GAME_TILEMAPS_MAX) {
        Game_ThrowError("Tilemap access outside of bounds");
        return NULL;
    }
    return &Game_TileMapManager.tilemaps[id];
}

extern void Game_RenderTiledImage(Game_TiledImage *image, Transform *transform, SDL_RendererFlip flip) {
    const SDL_Rect src_rect = {
        .x = image->tilemap->tile_width * image->tile_x + image->padding,
        .y = image->tilemap->tile_height * image->tile_y + image->padding,
        .w = image->tilemap->tile_width - image->padding,
        .h = image->tilemap->tile_height - image->padding
    };

    const SDL_FRect dst_rect = {
        .x = transform->position.x,
        .y = transform->position.y,
        .w = transform->size.x,
        .h = transform->size.y
    };

    SDL_Renderer *renderer = Game_GetRenderer();
    SDL_RenderCopyExF(renderer, image->tilemap->texture, &src_rect, &dst_rect, 0.0, NULL, flip);
}
