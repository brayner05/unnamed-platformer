#include "player.h"
#include "../../camera.h"
#include "../../../internal/animation.h"
#include "../../../math/transform.h"
#include "../../../internal/image.h"
#include "../../../internal/internals.h"
#include "../../../game/physics/physics.h"

#define ANIMATION_SPEED_MS 100
#define FACE_LEFT SDL_FLIP_HORIZONTAL
#define FACE_RIGHT SDL_FLIP_NONE

#define MOVEMENT_SPEED 3.0f
#define MASS 5.0f

#define JUMP_FORCE (-GRAVITY_PX_PER_FRAME_SQUARED * MASS - 10.0f)

// The direction the player is looking:
static SDL_RendererFlip facing_direction = FACE_RIGHT;

// Flag tracking whether the player is moving or not,
// used for animation:
static bool moving = false;

// Falling flag used for gravity:
static bool falling = true;

// The players transform component:
static Transform transform = {
    .position = { 0, 0 },
    .size = {
        .x = 1.5f * METER_FACTOR,
        .y = 1.5f * METER_FACTOR
    }
};

// The graphical representation of the player:
static Game_TiledSprite sprite = {
    .tilemap = GAME_TILEMAP_KNIGHT,
    .tile_x = 0,
    .tile_y = 0,
    .padding = 8
};;

Game_PhysicsObject physics_object = {
    .mass = MASS,
    .velocity = { 0, 0 }
};

Game_ColliderObject collider_object;

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
    collider_object.bounds = &transform;
    collider_object.id = "player";
    Physics_RegisterCollider(&collider_object);
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
    physics_object.velocity.y = JUMP_FORCE;
    falling = true;
}

static void FocusCamera(void) {
    const Transform focus_point = {
        .position = {
            .x = transform.position.x + 200,
            .y = transform.position.y - 200
        },
        .size = transform.size
    };
    Camera_LookAt(&focus_point);
}

static void UpdatePosition(void) {
    transform.position = Vector2D_Add(&transform.position, &physics_object.velocity);
}

extern void Player_Update(void) {
    // Gravity
    Physics_ApplyGravity(&physics_object);

    // Idle
    if (Game_GetAxis(AXIS_HORIZONTAL) == 0)
        Game_PlayAnimation(IdleAnimation, ANIMATION_SPEED_MS);

    // Movement
    if (Game_GetAxis(AXIS_HORIZONTAL) > 0) MoveRight();
    if (Game_GetAxis(AXIS_HORIZONTAL) < 0) MoveLeft();

    // Jumping
    if (!falling && Game_GetAxis(AXIS_JUMP))
        Jump();

    UpdatePosition();
    FocusCamera();

    // TEMPORARY START
    const Vector2D window_dimensions = Game_GetWindowSize();
    if (transform.position.y + transform.size.y >= 200) {
        transform.position.y = 200 - transform.size.y;
        physics_object.velocity.y = 0;
        falling = false;
    }
    // TEMPORARY END
}
