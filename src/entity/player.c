#include "player.h"
#include "../math/transform.h"
#include "../internal/image.h"
#include "../internal/internals.h"

#define METER_FACTOR 128
#define MOVEMENT_SPEED 3.5f
#define FACE_LEFT SDL_FLIP_HORIZONTAL
#define FACE_RIGHT SDL_FLIP_NONE

static Transform transform = { 0 };
static Game_TiledImage sprite;
static bool moving = false;
static SDL_RendererFlip facing_direction = FACE_RIGHT;

static void SprintAnimation(void) {
    if (!moving) {
        sprite.tile_y = 2;
        moving = true;
    }

    if (sprite.tile_x == 7) {
        sprite.tile_y = 2 + (sprite.tile_y + 1) % 2;
    }

    sprite.tile_x = (sprite.tile_x + 1) % 8;
}

static void IdleAnimation(void) {
    moving = false;
    sprite.tile_x = (sprite.tile_x + 1) % 4;
    sprite.tile_y = 0;
}

extern void Player_Init(void) {
    const Game_TiledImage knight = {
        .tilemap = Game_GetTileMap(GAME_TILEMAP_KNIGHT),
        .tile_x = 0,
        .tile_y = 0
    };
    sprite = knight;
    transform.size.x = 128;
    transform.size.y = 128;
}

extern Transform *Player_GetTransform(void) {
    return &transform;
}

extern void Player_Render(void) {
    Game_RenderTiledImage(&sprite, &transform, facing_direction);
}

extern void Player_Update(void) {
    // Idle
    if (Game_GetAxis(AXIS_HORIZONTAL) == 0) {
        IdleAnimation();
    }

    // Moving right
    if (Game_GetAxis(AXIS_HORIZONTAL) > 0) {
        facing_direction = FACE_LEFT;
        SprintAnimation();
        transform.position.x += MOVEMENT_SPEED * METER_FACTOR / 60.0f;
    }

    // Moving left
    if (Game_GetAxis(AXIS_HORIZONTAL) < 0) {
        facing_direction = FACE_LEFT;
        SprintAnimation();
        transform.position.x -= MOVEMENT_SPEED * METER_FACTOR / 60.0f;
    }
}