#ifndef UNNAMED_GAME_CAMERA_H
#define UNNAMED_GAME_CAMERA_H
#include "../math/transform.h"

namespace camera {
    Transform& GetTransform();
    void Init();
    void Translate(const Vector2D& offset);
    void LookAt(const Transform& target);
}

extern void Camera_Init(void);

extern Transform *Camera_GetTransform(void);

extern void Camera_Translate(const Vector2D *offset);

extern void Camera_LookAt(const Transform *target);

#endif //UNNAMED_GAME_CAMERA_H