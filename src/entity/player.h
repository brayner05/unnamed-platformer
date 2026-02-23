#ifndef UNNAMED_GAME_PLAYER_H
#define UNNAMED_GAME_PLAYER_H
#include "../math/transform.h"
#include "../internal/image.h"

extern void Player_Init(Game_TiledImage *new_sprite);

extern Transform *Player_GetTransform(void);

extern void Player_Render(void);

extern void Player_Update(void);

#endif //UNNAMED_GAME_PLAYER_H