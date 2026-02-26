#include "physics.h"

#define COLLIDER_LIST_BLOCK_SIZE 32
static size_t collider_count = 0;
static size_t collider_capacity = COLLIDER_LIST_BLOCK_SIZE;
static Game_ColliderObject *colliders = NULL;

extern int Physics_EnableCollision(void) {
    Game_ColliderObject *collider_list = (Game_ColliderObject *) malloc(collider_capacity * sizeof(Game_ColliderObject));
    if (collider_list == NULL) {
        Game_ThrowError("OUT OF MEMORY / CANNOT ENABLE COLLISION");
        return -1;
    }
    colliders = collider_list;
    return 0;
}

extern int Physics_RegisterCollider(const Game_ColliderObject *collider) {
    if (collider_count >= collider_capacity) {
        collider_capacity += COLLIDER_LIST_BLOCK_SIZE;
        Game_ColliderObject *tmp = realloc(colliders, collider_capacity);
        if (tmp == NULL) {
            Game_ThrowError("OUT OF MEMORY / CANNOT REGISTER COLLIDER");
            return -1;
        }
        colliders = tmp;
    }
    colliders[collider_count++] = *collider;
    return 0;
}

extern void Physics_DisableCollision(void) {
    if (colliders != NULL) {
        free(colliders);
        collider_count = 0;
        colliders = NULL;
    }
}

extern void Physics_ApplyGravity(Game_PhysicsObject *object) {
    object->velocity.y += object->mass * GRAVITY_PX_PER_FRAME_SQUARED;
}
