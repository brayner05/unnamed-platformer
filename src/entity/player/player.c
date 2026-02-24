#include "player.h"
#include "../../internal/animation.h"
#include "../../math/transform.h"
#include "../../internal/image.h"
#include "../../internal/internals.h"

#define ANIMATION_SPEED_MS 100
#define FACE_LEFT SDL_FLIP_HORIZONTAL
#define FACE_RIGHT SDL_FLIP_NONE

#define MOVEMENT_SPEED 1.5f
#define WEIGHT 5.0f
#define GRAVITY (9.8f / METER_FACTOR)

#define JUMP_FORCE (-GRAVITY - 7.0f)

// The graphical representation of the player:
static Game_TiledImage sprite;

// TODO: add abstraction
// The direction the player is looking:
static SDL_RendererFlip facing_direction = FACE_RIGHT;

// The players transform component:
static Transform transform = { 0 };

// The velocity of the player:
static Vector2D velocity = { 0, 0 };

// Flag tracking whether the player is moving or not,
// used for animation:
static bool moving = false;

// Falling flag used for gravity:
static bool falling = true;

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

/**
 * Initialize all dependency components.
 */
extern void Player_Init(void) {
    const Game_TiledImage knight = {
        .tilemap = Game_GetTileMap(GAME_TILEMAP_KNIGHT),
        .tile_x = 0,
        .tile_y = 0
    };
    sprite = knight;
    transform.size.x = 1 * METER_FACTOR;
    transform.size.y = 1 * METER_FACTOR;
}

extern Transform *Player_GetTransform(void) {
    return &transform;
}

extern void Player_Render(void) {
    Game_RenderTiledImage(&sprite, &transform, facing_direction);
}

static void MoveRight(void) {
    facing_direction = FACE_RIGHT;
    Game_PlayAnimation(SprintAnimation, ANIMATION_SPEED_MS);
    transform.position.x += MOVEMENT_SPEED * METER_FACTOR / TARGET_FPS;
}

static void MoveLeft(void) {
    facing_direction = FACE_LEFT;
    Game_PlayAnimation(SprintAnimation, ANIMATION_SPEED_MS);
    transform.position.x -= MOVEMENT_SPEED * METER_FACTOR / TARGET_FPS;
}

static void Jump(void) {
    velocity.y = JUMP_FORCE;
    falling = true;
}

extern void Player_Update(void) {
    // Gravity
    if (falling) {
        velocity.y += WEIGHT * GRAVITY;
    }

    // Idle
    if (Game_GetAxis(AXIS_HORIZONTAL) == 0) {
        Game_PlayAnimation(IdleAnimation, ANIMATION_SPEED_MS);
    }

    // Moving right
    if (Game_GetAxis(AXIS_HORIZONTAL) > 0)
        MoveRight();

    // Moving left
    if (Game_GetAxis(AXIS_HORIZONTAL) < 0)
        MoveLeft();

    // Jumping
    if (!falling && Game_GetAxis(AXIS_JUMP))
        Jump();

    if (transform.position.y >= 200) {
        transform.position.y = 200;
        falling = false;
    }

    transform.position = Vector2D_Add(&transform.position, &velocity);
}
