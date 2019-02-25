#include "v2.h"
#include <stdlib.h>
#include <math.h>

float rand_normalized() {
    return (float) rand() / (float) RAND_MAX;
}

float v2_length(struct v2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

struct v2 v2_normalized(struct v2 v) {
    return v2_div_scalar(v, v2_length(v));
}

struct v2 v2_rand_normalized() {
    struct v2 v = { .x = rand_normalized(), .y = rand_normalized() };
    return v2_normalized(v);
}

struct v2 v2_truncated(struct v2 v, float max) {
    float t = v2_length(v) / max;
    if (t > 1.0f) {
        return v2_div_scalar(v, t);
    }
    return v;
}

struct v2 v2_add(struct v2 a, struct v2 b) {
    return (struct v2) {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

struct v2 v2_sub(struct v2 a, struct v2 b) {
    return (struct v2) {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

struct v2 v2_dot(struct v2 a, struct v2 b) {
    return (struct v2) {
        .x = a.x * b.x,
        .y = a.y * b.y
    };
}

struct v2 v2_mult_scalar(struct v2 v, float c) {
    return (struct v2) {
        .x = v.x * c,
        .y = v.y * c
    };
}

struct v2 v2_div_scalar(struct v2 v, float c) {
    return (struct v2) {
        .x = v.x / c,
        .y = v.y / c
    };
}