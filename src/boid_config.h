#ifndef BOID_CONFIG_H
#define BOID_CONFIG_H

/**
 * Holds all the values needed to initialize the boid simulation.
 */
struct boid_config {
    int screen_width;
    int screen_height;
    float width;
    float height;
    int n;
    float boid_size;
    float max_speed;
    float neighbor_radius;
    float x_separation;
    float x_cohesion;
    float x_alignment;
    float x_bounds;
};

/**
 * Parse config file to get initialization values for boid system.
 * Return 1 if successful, 0 otherwise.
 */
int parse_config(struct boid_config *config, const char *file_name);

#endif