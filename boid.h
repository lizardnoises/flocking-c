#ifndef BOID_H
#define BOID_H

#include "raymath.h"

struct boid_neighbors {
    float radius;
    struct boid **boids;
    unsigned n;
};

struct boid {
    Vector2 position;
    Vector2 velocity;
    float max_speed;
    struct boid_neighbors neighbors;
};

struct boid_state {
    struct boid *boids;
    unsigned n;
    float width;
    float height;
    float x_separation;
    float x_cohesion;
    float x_alignment;
    float x_bounds;
    float boid_size;
};

struct boid_parameters {
    unsigned n;
    float width;
    float height;
    float max_speed;
    float neighbor_radius;
    float x_separation;
    float x_cohesion;
    float x_alignment;
    float x_bounds;
    float boid_size;
};

struct boid_state *boid_state_new(struct boid_parameters *params);
void boid_state_delete(struct boid_state *state);
void boid_state_update(struct boid_state *state);
void boid_update_neighbors(struct boid_state *state);
Vector2 boid_separation(struct boid *b);
Vector2 boid_cohesion(struct boid *b);
Vector2 boid_alignment(struct boid *b);
Vector2 boid_bounds(struct boid *b, float x_min, float x_max, float y_min, float y_max);
Vector2 boid_avoid_point(struct boid *b, float x, float y);
Vector2 Vector2Clip(Vector2 v, float max);

#endif