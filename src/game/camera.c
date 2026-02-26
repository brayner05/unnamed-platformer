#include "camera.h"
#include "../math/transform.h"
#include "../math/vector.h"
#include "../internal/internals.h"

static Transform transform;

extern void Camera_Init(void) {
    const Transform tmp = {
        .position = { 0, 0 },
        .size = Game_GetWindowSize()
    };
    transform = tmp;
}

extern Transform *Camera_GetTransform(void) {
    return &transform;
}

extern void Camera_Translate(const Vector2D *offset) {
    const Vector2D new_pos = Vector2D_Add(&transform.position, offset);
    transform.position = new_pos;
}

extern void Camera_LookAt(const Transform *target) {
    transform.position.x = target->position.x - 0.5f * (transform.size.x - target->size.x);
    transform.position.y = target->position.y - 0.5f * (transform.size.y - target->size.y);
}