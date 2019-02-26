#include "boids.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float rand_normalized() {
    return (float) rand() / (float) RAND_MAX;
}

Vector2 Vector2Clip(Vector2 v, float max) {
    float length = Vector2Length(v);
    if (length > max) {
        v = Vector2Divide(v, length / max);
    }
    return v;
}

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
        b->force = (Vector2) { .x = 0.0f, .y = 0.0f };
        b->velocity = (Vector2) {
            .x = rand_normalized() * max_speed,
            .y = rand_normalized() * max_speed
        };
        b->position = (Vector2) {
            .x = rand_normalized() * width,
            .y = rand_normalized() * height
        };
        b->fov_radius = fov_radius;
    }
}

void integrate(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *b = &(state->boids[i]);
        b->force = Vector2Clip(b->force, b->max_force);
        Vector2 acceleration = Vector2Divide(b->force, b->mass);
        b->velocity = Vector2Add(b->velocity, acceleration);
        b->velocity = Vector2Clip(b->velocity, b->max_speed);
        b->position = Vector2Add(b->position, b->velocity);
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
            Vector2 pos_dif = Vector2Subtract(bi->position, bj->position);
            float r = Vector2Length(pos_dif);
            if (r <= bi->fov_radius) {
                Vector2 force_dir = Vector2Normalize(pos_dif);
                Vector2 force = Vector2Divide(force_dir, r);
                bi->force = Vector2Add(bi->force, force);
            }
        }
    }
}

void cohesion(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *bi = &(state->boids[i]);
        unsigned n = 0;
        Vector2 center = { .x = 0.0f, .y = 0.0f };
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            struct boid *bj = &(state->boids[j]);
            Vector2 pos_dif = Vector2Subtract(bi->position, bj->position);
            float r = Vector2Length(pos_dif);
            if (r <= bi->fov_radius) {
                center = Vector2Add(center, bj->position);
                n++;
            }
        }
        if (n > 0) {
            center = Vector2Divide(center, n);
            Vector2 pos_dif = Vector2Subtract(center, bi->position);
            Vector2 force_dir = Vector2Normalize(pos_dif);
            Vector2 force = Vector2Divide(force_dir, bi->fov_radius / Vector2Length(pos_dif));
            bi->force = Vector2Add(bi->force, force);
        }
    }
}

void alignment(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *bi = &(state->boids[i]);
        unsigned n = 0;
        Vector2 avg_velocity = Vector2Zero();
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            struct boid *bj = &(state->boids[j]);
            Vector2 pos_dif = Vector2Subtract(bi->position, bj->position);
            float r = Vector2Length(pos_dif);
            if (r <= bi->fov_radius) {
                avg_velocity = Vector2Add(avg_velocity, bj->velocity);
                n++;
            }
        }
        if (n > 0) {
            avg_velocity = Vector2Divide(avg_velocity, n);
            Vector2 velocity_dif = Vector2Subtract(avg_velocity, bi->velocity);
            Vector2 force_dir = Vector2Normalize(velocity_dif);
            Vector2 force = Vector2Scale(force_dir, Vector2Length(velocity_dif));
            bi->force = Vector2Add(bi->force, force);
        }
    }
}