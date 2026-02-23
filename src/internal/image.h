#ifndef UNNAMED_GAME_IMAGE_H
#define UNNAMED_GAME_IMAGE_H
#include "internals.h"
#include "../math/transform.h"

extern SDL_Surface *Game_LoadImage(const char *path);

extern void Game_RenderImage(SDL_Surface *image, Transform *transform);

#endif //UNNAMED_GAME_IMAGE_H