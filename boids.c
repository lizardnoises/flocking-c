#include "boids.h"
#include "v2.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void init_boids(struct boid_state *state,
                struct boid *boids,
                int n,
                float width,
                float height,
                float mass,
                float max_speed,
                float max_force,
                float fov_radius) {
    state->boids = boids;
    state->n = n;
    state->width = width;
    state->height = height;

    for (unsigned i = 0; i < n; i++) {
        struct boid *b = &(boids[i]);
        b->mass = mass;
        b->max_force = max_force;
        b->max_speed = max_speed;
        b->force = (struct v2) { .x = 0.0f, .y = 0.0f };
        b->velocity = (struct v2) {
            .x = rand_normalized() * max_speed,
            .y = rand_normalized() * max_speed
        };
        b->position = (struct v2) {
            .x = rand_normalized() * width,
            .y = rand_normalized() * height
        };
        b->fov_radius = fov_radius;
    }
}

void integrate(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *b = &(state->boids[i]);
        b->force = v2_truncated(b->force, b->max_force);
        struct v2 acceleration = v2_div_scalar(b->force, b->mass);
        b->velocity = v2_add(b->velocity, acceleration);
        b->velocity = v2_truncated(b->velocity, b->max_speed);
        b->position = v2_add(b->position, b->velocity);
        if (b->position.x > state->width) {
            b->position.x -= state->width;
        }
        if (b->position.x < 0.0f) {
            b->position.x += state->width;
        }
        if (b->position.y > state->height) {
            b->position.y -= state->height;
        }
        if (b->position.y < 0.0f) {
            b->position.y += state->height;
        }
        //printf("pos: %f %f\n", b->position.x, b->position.y);
    }
}

void separation(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *bi = &(state->boids[i]);
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            struct boid *bj = &(state->boids[j]);
            struct v2 pos_dif = v2_sub(bi->position, bj->position);
            float r = v2_length(pos_dif);
            if (r <= bi->fov_radius) {
                struct v2 force_dir = v2_normalized(pos_dif);
                struct v2 force = v2_div_scalar(force_dir, r);
                bi->force = v2_add(bi->force, force);
            }
        }
    }
}

void cohesion(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *bi = &(state->boids[i]);
        unsigned n = 0;
        struct v2 center = { .x = 0.0f, .y = 0.0f };
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            struct boid *bj = &(state->boids[j]);
            struct v2 pos_dif = v2_sub(bi->position, bj->position);
            float r = v2_length(pos_dif);
            if (r <= bi->fov_radius) {
                center = v2_add(center, bj->position);
                n++;
            }
        }
        if (n > 0) {
            center = v2_div_scalar(center, n);
            struct v2 pos_dif = v2_sub(center, bi->position);
            struct v2 force_dir = v2_normalized(pos_dif);
            struct v2 force = v2_mult_scalar(force_dir, v2_length(pos_dif) / bi->fov_radius);
            bi->force = v2_add(bi->force, force);
        }
    }
}

void alignment(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *bi = &(state->boids[i]);
        unsigned n = 0;
        struct v2 avg_velocity = { .x = 0.0f, .y = 0.0f };
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            struct boid *bj = &(state->boids[j]);
            struct v2 pos_dif = v2_sub(bi->position, bj->position);
            float r = v2_length(pos_dif);
            if (r <= bi->fov_radius) {
                avg_velocity = v2_add(avg_velocity, bj->velocity);
                n++;
            }
        }
        if (n > 0) {
            avg_velocity = v2_div_scalar(avg_velocity, n);
            struct v2 velocity_dif = v2_sub(avg_velocity, bi->velocity);
            struct v2 force_dir = v2_normalized(velocity_dif);
            struct v2 force = v2_mult_scalar(force_dir, v2_length(velocity_dif));
            bi->force = v2_add(bi->force, force);
        }
    }
}