#include "camera.hpp"
#include "../math/transform.h"
#include "../math/vector.h"
#include "../internal/internals.hpp"

namespace camera {
    static Transform transform {  };
}

void camera::Init() {
    const Transform tmp = {
        .position = { 0, 0 },
        .size = internals::GetWindowSize()
    };
    transform = tmp;
}

Transform &camera::GetTransform() {
    return transform;
}

void camera::Translate(const Vector2D &offset) {
    const Vector2D new_pos = Vector2D_Add(&transform.position, &offset);
    transform.position = new_pos;
}

extern void camera::LookAt(const Transform& target) {
    transform.position.x = target.position.x - 0.5f * (transform.size.x - target.size.x);
    transform.position.y = target.position.y - 0.5f * (transform.size.y - target.size.y);
}