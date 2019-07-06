#include "boid.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Return a copy of the vector with the magnitude restricted to at most max.
 */
static Vector2 Vector2Clip(Vector2 v, float max) {
    float length = Vector2Length(v);
    if (length > max) {
        float r = length / max;
        v = Vector2Divide(v, r);
    }
    return v;
}

/**
 * Return a random float normalized to the interval (0, 1).
 */
static float rand_normalized() {
    return (float) rand() / (float) RAND_MAX;
}

/**
 * Wrap around the given value to fit between min and max.
 */
static float wrap(float value, float min, float max) {
    if (value < min) {
        value += (max - min);
    }
    else if (value > max) {
        value -= (max - min);
    }
    return value;
}

struct boid_state *boid_state_new(struct boid_parameters *p) {
    struct boid_state *state = malloc(sizeof(struct boid_state));
    state->n = p->n;
    state->width = p->width;
    state->height = p->height;

    struct boid *b = malloc(sizeof(struct boid) * p->n);
    for (unsigned i = 0; i < p->n; i++) {
        b[i].max_speed = p->max_speed;
        b[i].position.x = rand_normalized() * p->width;
        b[i].position.y = rand_normalized() * p->height;
        b[i].velocity = Vector2Clip((Vector2) {
            .x = rand_normalized() * p->max_speed,
            .y = rand_normalized() * p->max_speed
        }, p->max_speed);

        b[i].neighbors.boids = malloc(sizeof(struct boid *) * (p->n - 1));
        b[i].neighbors.n = 0;
        b[i].neighbors.radius = p->neighbor_radius;
    }
    state->boids = b;

    state->boid_size = p->boid_size;
    state->x_alignment = p->x_alignment;
    state->x_cohesion = p->x_cohesion;
    state->x_separation = p->x_separation;
    state->x_bounds = p->x_bounds;

    return state;
}

void boid_state_delete(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        free(state->boids[i].neighbors.boids);
    }
    free(state->boids);
    free(state);
}

void boid_state_update(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        struct boid *b = &(state->boids[i]);

        float max_d = fmaxf(state->width, state->height);
        float x_min = 0.10f * max_d;
        float x_max = state->width - x_min;
        float y_min = x_min;
        float y_max = state->height - y_min;

        b->velocity = Vector2Add(b->velocity, Vector2Scale(boid_separation(b), state->x_separation));
        b->velocity = Vector2Add(b->velocity, Vector2Scale(boid_cohesion(b), state->x_cohesion));
        b->velocity = Vector2Add(b->velocity, Vector2Scale(boid_alignment(b), state->x_alignment));
        b->velocity = Vector2Add(b->velocity, Vector2Scale(boid_bounds(b, x_min, x_max, y_min, y_max), state->x_bounds));
        b->velocity = Vector2Clip(b->velocity, b->max_speed);
        b->velocity = Vector2Add(b->velocity, Vector2Scale(boid_avoid_point(b, GetMouseX(), GetMouseY()), 20.0f));

        b->position = Vector2Add(b->position, b->velocity);
    }
}

void boid_update_neighbors(struct boid_state *state) {
    struct boid *b = state->boids;
    for (unsigned i = 0; i < state->n; i++) {
        b[i].neighbors.n = 0;
        for (unsigned j = 0; j < state->n; j++) {
            if (i == j) {
                continue;
            }
            Vector2 distance = Vector2Subtract(b[i].position, b[j].position);
            if (Vector2Length(distance) <= b[i].neighbors.radius) {
                b[i].neighbors.boids[b[i].neighbors.n] = &b[j];
                b[i].neighbors.n++;
            }
        }
    }
}

Vector2 boid_separation(struct boid *b) {
    Vector2 acceleration = Vector2Zero();
    for (unsigned i = 0; i < b->neighbors.n; i++) {
        Vector2 displacement = Vector2Subtract(b->position, b->neighbors.boids[i]->position);
        displacement = Vector2Divide(Vector2Normalize(displacement), Vector2Length(displacement));
        acceleration = Vector2Add(acceleration, displacement);
    }
    return acceleration;
}

Vector2 boid_cohesion(struct boid *b) {
    Vector2 average_position = Vector2Zero();
    for (unsigned i = 0; i < b->neighbors.n; i++) {
        average_position = Vector2Add(average_position, b->neighbors.boids[i]->position);
    }
    Vector2 acceleration = Vector2Zero();
    if (b->neighbors.n > 0) {
        average_position = Vector2Divide(average_position, b->neighbors.n);
        acceleration = Vector2Subtract(average_position, b->position);
    }
    return acceleration;
}

Vector2 boid_alignment(struct boid *b) {
    Vector2 acceleration = Vector2Zero();
    for (unsigned i = 0; i < b->neighbors.n; i++) {
        Vector2 displacement = Vector2Subtract(b->neighbors.boids[i]->position, b->position);
        acceleration = Vector2Add(acceleration, Vector2Divide(Vector2Normalize(b->neighbors.boids[i]->velocity), Vector2Length(displacement)));
    }
    return acceleration;
}

Vector2 boid_bounds(struct boid *b, float x_min, float x_max, float y_min, float y_max) {
    Vector2 acceleration = Vector2Zero();
    if (b->position.x < x_min) {
        acceleration.x = x_min - b->position.x;
    }
    else if (b->position.x > x_max) {
        acceleration.x = x_max - b->position.x;
    }
    if (b->position.y < y_min) {
        acceleration.y = y_min - b->position.y;
    }
    else if (b->position.y > y_max) {
        acceleration.y = y_max - b->position.y;
    }
    return acceleration;
}

Vector2 boid_avoid_point(struct boid *b, float x, float y) {
    Vector2 acceleration = Vector2Zero();
    Vector2 displacement = Vector2Subtract(b->position, (Vector2) {x, y});
    float distance = Vector2Length(displacement);
    if (distance < b->neighbors.radius) {
        acceleration = Vector2Divide(Vector2Normalize(displacement), distance);
    }
    return acceleration;
}