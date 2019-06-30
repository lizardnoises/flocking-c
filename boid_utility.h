#ifndef BOID_UTILITY_H
#define BOID_UTILITY_H

#include "raymath.h"
#include <stdlib.h>

/**
 * Return a copy of the vector with the magnitude restricted to at most max.
 */
Vector2 Vector2Clip(Vector2 v, float max);

/**
 * Return a random float normalized to the interval (0, 1).
 */
float rand_normalized();

/**
 * Wrap around the given value to fit between min and max.
 */
float wrap(float value, float min, float max);

#endif