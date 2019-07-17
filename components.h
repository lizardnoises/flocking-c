#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"
#include "entities.h"

struct position_component {
    Vector2 position;
    float rotation;
};

struct move_component {
    Vector2 velocity;
    float max_speed;
};

struct neighborhood_component {
    float radius;
};

struct alignment_component {
    float weight;
};

struct bounds_component {
    float weight;
};

struct cohesion_component {
    float weight;
};

struct separation_component {
    float weight;
};

/**
 * Consider implementing with bitmasks in the future.
 */
struct component_flags {
    unsigned int position : 1;
    unsigned int move : 1;
    unsigned int neighborhood : 1;
    unsigned int alignment : 1;
    unsigned int bounds : 1;
    unsigned int cohesion : 1;
    unsigned int separation : 1;
};

struct component_manager {
    struct position_component position[MAX_ENTITIES];
    struct move_component move[MAX_ENTITIES];
    struct neighborhood_component neighborhood[MAX_ENTITIES];
    struct alignment_component alignment[MAX_ENTITIES];
    struct bounds_component bounds[MAX_ENTITIES];
    struct cohesion_component cohesion[MAX_ENTITIES];
    struct separation_component separation[MAX_ENTITIES];
};

#endif