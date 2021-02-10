#include "vector_aux.h"

Vector2 Vector2Clip(Vector2 v, float max) {
    float length = Vector2Length(v);
    if (length > max) {
        float r = length / max;
        v = Vector2Divide(v, r);
    }
    return v;
}

Vector2 Vector2Rotate(Vector2 v, float angle) {
    float angle_rad = DEG2RAD * angle;
    float sa = sinf(angle_rad);
    float ca = cosf(angle_rad);
    Vector2 v2 = {
        ca * v.x - sa * v.y,
        sa * v.x + ca * v.y
    };
    return v2;
}