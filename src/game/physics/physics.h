#ifndef UNNAMED_GAME_GRAVITY_H
#define UNNAMED_GAME_GRAVITY_H
#include <stdbool.h>
#include "../../internal/internals.h"
#include "../../math/vector.h"
#include "../../math/transform.h"

/**
 * Since the engine computes gravity every frame rather than every second,
 * it needs to be scaled down from m/s^2 to px/frame^2.
 *
 * The math to get here:
 * m/s^2 * px/m => px/s^2
 * px/s^2 / (f/s)^2 => px/s^2 / (f^2/s^2)
 *                  => px/s^2 * s^2/f^2
 *                  => px/f^2
 */
#define GRAVITY_M_PER_S_SQUARED      (9.8f)
#define GRAVITY_PX_PER_FRAME_SQUARED (GRAVITY_M_PER_S_SQUARED * METER_FACTOR / (TARGET_FPS * TARGET_FPS))

typedef struct {
    float mass;
    Vector2D velocity;
} Game_PhysicsObject;

extern void Physics_ApplyGravity(Game_PhysicsObject *object);

typedef struct {
    char *id;
    Transform *bounds;
} Game_ColliderObject;

extern int Physics_EnableCollision(void);

extern int Physics_RegisterCollider(const Game_ColliderObject *collider);

extern void Physics_DisableCollision(void);
#endif //UNNAMED_GAME_GRAVITY_H