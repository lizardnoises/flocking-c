#include "boid_utility.h"

Vector2 Vector2Clip(Vector2 v, float max) {
    float length = Vector2Length(v);
    if (length > max) {
        float r = length / max;
        v = Vector2Divide(v, r);
    }
    return v;
}

float rand_normalized() {
    return (float) rand() / (float) RAND_MAX;
}

float wrap(float value, float min, float max) {
    if (value < min) {
        value += (max - min);
    }
    else if (value > max) {
        value -= (max - min);
    }
    return value;
}