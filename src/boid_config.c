/**
 * Consider mapping parameter strings to corresponding struct fields,
 * looping through each pair, and matching on the strings.
 * 
 * MATCH macro idea from https://github.com/benhoyt/inih.
 */

#include "boid_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

/**
 * Interpret and store the value in the config field associated with the name.
 * Return 1 if successful, 0 otherwise.
 */
static int handle_parameter(struct boid_config *config, const char *name,
                            const char *value) {
    #define MATCH(n) strcmp(name, n) == 0
    if (MATCH("screen_width")) {
        config->screen_width = atoi(value);
    }
    else if (MATCH("screen_height")) {
        config->screen_height = atoi(value);
    }
    else if (MATCH("width")) {
        config->width = atof(value);
    }
    else if (MATCH("height")) {
        config->height = atof(value);
    }
    else if (MATCH("n")) {
        config->n = atoi(value);
    }
    else if (MATCH("boid_size")) {
        config->boid_size = atof(value);
    }
    else if (MATCH("max_speed")) {
        config->max_speed = atof(value);
    }
    else if (MATCH("neighbor_radius")) {
        config->neighbor_radius = atof(value);
    }
    else if (MATCH("x_separation")) {
        config->x_separation = atof(value);
    }
    else if (MATCH("x_cohesion")) {
        config->x_cohesion = atof(value);
    }
    else if (MATCH("x_alignment")) {
        config->x_alignment = atof(value);
    }
    else if (MATCH("x_bounds")) {
        config->x_bounds = atof(value);
    }
    else {
        fprintf(stderr, "Unrecognized parameter: %s\n", name);
        return 0;
    }
    #undef MATCH
    return 1;
}

/**
 * Parse config file into the given config object.
 * Return 1 if successful, 0 otherwise.
 */
int parse_config(struct boid_config *config, const char *file_name) {
    FILE *input = fopen(file_name, "r");
    if (!input) {
        perror("Failed to open the config file");
        return 0;
    }
    char buffer[BUFFER_SIZE];
    char name[BUFFER_SIZE];
    char value[BUFFER_SIZE];
    while (buffer == fgets(buffer, BUFFER_SIZE, input)) {
        if (sscanf(buffer, "%[^= ]=%s", name, value) != 2) {
            fprintf(stderr, "Failed to parse name, value pair from: \"%s\"",
                   buffer);
            return 0;
        }
        if (handle_parameter(config, name, value) == 0) {
            return 0;
        }
    }
    fclose(input);
    return 1;
}