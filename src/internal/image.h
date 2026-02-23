#ifndef UNNAMED_GAME_IMAGE_H
#define UNNAMED_GAME_IMAGE_H
#include "internals.h"
#include "../math/transform.h"

typedef struct {
    SDL_Surface *surface;
    int tile_width;
    int tile_height;
} Game_TileMap;

typedef struct {
    Game_TileMap *tilemap;
    int tile_x;
    int tile_y;
} Game_TiledImage;

extern SDL_Surface *Game_LoadImage(const char *path);

extern void Game_RenderImage(SDL_Surface *image, Transform *transform);

extern void Game_RenderTiledImage(Game_TiledImage *image, Transform *transform);

extern int Game_InitTileMaps(void);

extern Game_TileMap *Game_GetTileMap(size_t id);

extern int Game_LoadTilemap(const char *path, int tile_width, int tile_height);

#endif //UNNAMED_GAME_IMAGE_H