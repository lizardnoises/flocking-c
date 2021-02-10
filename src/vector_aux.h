#ifndef VECTOR_AUX_H
#define VECTOR_AUX_H

#include "raymath.h"

/**
 * Return a copy of the vector with the magnitude restricted to at most max.
 */
Vector2 Vector2Clip(Vector2 v, float max);

/**
 * Rotate a 2D vector about 0,0.
 */
Vector2 Vector2Rotate(Vector2 v, float angle);

#endif