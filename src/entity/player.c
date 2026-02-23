#include "player.h"
#include "../math/transform.h"
#include "../internal/image.h"

static Transform transform = { 0 };
static Game_TiledImage sprite;

extern void Player_Init(Game_TiledImage *new_sprite) {
    transform.size.x = 128;
    transform.size.y = 128;
    sprite.tilemap = new_sprite->tilemap;
    sprite.tile_x = new_sprite->tile_x;
    sprite.tile_y = new_sprite->tile_y;
}

extern Transform *Player_GetTransform(void) {
    return &transform;
}

extern void Player_Render(void) {
    Game_RenderTiledImage(&sprite, &transform);
}

extern void Player_Update(void) {

}