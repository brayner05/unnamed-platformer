#ifndef UNNAMED_GAME_IMAGE_H
#define UNNAMED_GAME_IMAGE_H
#include "internals.h"
#include "../math/transform.h"

#define GAME_TILEMAPS_MAX 32

typedef struct {
    SDL_Texture *texture;
    int tile_width;
    int tile_height;
} Game_TileMap;

typedef enum {
    GAME_TILEMAP_KNIGHT         = 0,
    GAME_TILEMAP_WORLD          = 1,
    GAME_TILEMAP_SLIME_GREEN    = 2,
    GAME_TILEMAP_SLIME_PURPLE   = 3
} Game_TileMapId;

typedef struct {
    Game_TileMapId tilemap;
    int tile_x;
    int tile_y;
    int padding;
} Game_TiledSprite;

/**
 * Load an image from a file.
 * @param path
 * @return An SDL_Surface created from the file.
 */
extern SDL_Surface *Game_LoadImage(const char *path);

/**
 * Render an texture directly from a tilemap without needing to load
 * that texture specifically.
 * @param image
 * @param transform
 * @param flip
 */
extern void Game_RenderTiledImage(Game_TiledSprite *image, Transform *transform, SDL_RendererFlip flip);

extern int Game_InitTileMaps(void);

extern int Game_DestroyTileMap(Game_TileMapId id);

extern Game_TileMap *Game_GetTileMap(Game_TileMapId id);

extern int Game_LoadTilemap(size_t id, const char *path, int tile_width, int tile_height);

#endif //UNNAMED_GAME_IMAGE_H