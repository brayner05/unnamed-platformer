#include "physics.h"

#include <SDL2/SDL_timer.h>

extern void Physics_ApplyGravity(Game_PhysicsObject *object) {
    object->velocity.y += object->weight * GRAVITY_PX_PER_FRAME_SQUARED;
}
