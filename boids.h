#ifndef BOIDS_H
#define BOIDS_H

#include "v2.h"

struct boid {
    float mass;
    float max_speed;
    float max_force;
    float fov_radius;
    struct v2 position;
    struct v2 velocity;
    struct v2 force;
};

struct boid_state {
    struct boid* boids;
    int n;
    float width;
    float height;
};

void init_boids(struct boid_state *state,
                struct boid *boids,
                int n,
                float width,
                float height,
                float mass,
                float max_speed,
                float max_force,
                float fov_radius);
void separation(struct boid_state* state);
void cohesion(struct boid_state* state);
void alignment(struct boid_state* state);
void integrate(struct boid_state *state);

#endif