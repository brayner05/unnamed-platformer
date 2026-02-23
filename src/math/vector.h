#ifndef UNNAMED_GAME_VECTOR2D_H
#define UNNAMED_GAME_VECTOR2D_H
#include <math.h>

typedef struct {
    float x;
    float y;
} Vector2D;

static inline float Vector2D_Magnitude(const Vector2D *v) {
    return sqrtf(v->x * v->x + v->y * v->y);
}

static inline float Vector2D_Dot(const Vector2D *v1, const Vector2D *v2) {
    return ((v1->x * v2->x) + (v1->y * v2->y));
}

static inline Vector2D Vector2D_Add(const Vector2D *v1, const Vector2D *v2) {
    const Vector2D sum = {
        .x = (v1->x + v2->x),
        .y = (v1->y + v2->y)
    };
    return sum;
}

static inline Vector2D Vector2D_Subtract(const Vector2D *v1, const Vector2D *v2) {
    const Vector2D sum = {
        .x = (v1->x - v2->x),
        .y = (v1->y - v2->y)
    };
    return sum;
}

static inline Vector2D Vector2D_Multiply(const Vector2D *v, float factor) {
    const Vector2D product = {
        .x = factor * v->x,
        .y = factor * v->y
    };
    return product;
}


#endif //UNNAMED_GAME_VECTOR2D_H