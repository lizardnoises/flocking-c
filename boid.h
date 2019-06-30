#ifndef BOID_H
#define BOID_H

#include "raymath.h"

/**
 * Tracks all boids in the neighborhood radius of a given boid for use in
 * behaviour updates.
 */
struct boid_neighbors {
    float radius;
    struct boid **boids;
    unsigned n;
};

/**
 * Represents all the instance data needed to model a single boid.
 */
struct boid {
    Vector2 position;
    Vector2 velocity;
    float max_speed;
    struct boid_neighbors neighbors;
};

/**
 * Represents the collection of all boids and the shared attributes for
 * behaviour simulation.
 */
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

/**
 * Represents the parameters needed to initialize the boid simulation.
 */
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

/**
 * Create a boid simulation state using the given initialization parameters.
 */
struct boid_state *boid_state_new(struct boid_parameters *params);

/**
 * Clean-up memory for the simulation state and all associated boids.
 */
void boid_state_delete(struct boid_state *state);

/**
 * Integrate boid behaviors one step and update position and velocity.
 */
void boid_state_update(struct boid_state *state);

/**
 * Update neighborhoods for each boid in the simulation based on each boid's
 * neighborhood radius.
 */
void boid_update_neighbors(struct boid_state *state);

/**
 * Compute a partial velocity based one step of seperation behavior.
 * The boid will try not to get too close to it's neighbors.
 */
Vector2 boid_separation(struct boid *b);

/**
 * Compute a partial velocity based one step of cohesion behavior.
 * The boid will try to move toward the flock comprised of its neighbors.
 */
Vector2 boid_cohesion(struct boid *b);

/**
 * Compute a partial velocity based one step of alignment behavior.
 * The boid will try to match velocity (including direction) with the flock
 * comprised of its neighbors.
 */
Vector2 boid_alignment(struct boid *b);

/**
 * Compute a partial velocity, repelling the boid from the simulation.
 * boundaries. This rubberbands boids to the simulation frame.
 */
Vector2 boid_bounds(struct boid *b, float x_min, float x_max, float y_min, float y_max);

/**
 * Compute a partial velocity based on avoidance of the given point.
 * Boids prioritize avoidance based on proximity.
 */
Vector2 boid_avoid_point(struct boid *b, float x, float y);

#endif