#include "physics.h"

extern void Physics_ApplyGravity(Game_PhysicsObject *object) {
    object->velocity.y += object->mass * GRAVITY_PX_PER_FRAME_SQUARED;
}
