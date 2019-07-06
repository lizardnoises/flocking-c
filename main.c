#include "raylib.h"
#include "boid.h"
#include "boid_config.h"
#include <stdlib.h>
#include <time.h>

/**
 * Draw a single boid as a circle representing size and an intersecting line
 * segment representing direction.
 */
void draw_boid(struct boid *b, float radius, Color color) {
    DrawCircleLines(b->position.x, b->position.y, radius, color);
    Vector2 direction = Vector2Divide(Vector2Normalize(b->velocity),
                        1.0f / (2.0f * radius));
    DrawLine(b->position.x,
             b->position.y,
             b->position.x + direction.x,
             b->position.y + direction.y,
             color);
}

/**
 * Draws each boid in the state at it's current location with it's current
 * direction.
 */
void draw_boids(struct boid_state *state, Color color) {
    for (unsigned i = 0; i < state->n; i++) {
        draw_boid(&(state->boids[i]), state->boid_size, color);
    }
}

int main() {
    srand(time(NULL));
    
    struct boid_config config;
    if (parse_config(&config, "config.txt") == 0) {
        return EXIT_FAILURE;
    }

    const int screen_width = config.screen_width;
    const int screen_height = config.screen_height;

    struct boid_parameters params = {
        .n = config.n,
        .width = config.width,
        .height = config.height,
        .max_speed = config.max_speed,
        .neighbor_radius = config.neighbor_radius,
        .x_separation = config.x_separation,
        .x_cohesion = config.x_cohesion,
        .x_alignment = config.x_alignment,
        .x_bounds = config.x_bounds,
        .boid_size = config.boid_size
    };

    struct boid_state *state = boid_state_new(&params);

    InitWindow(screen_width, screen_height, "boids!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("boids!", state->width / 2 - 80, state->height / 2 - 20, 40, LIGHTGRAY);
        draw_boids(state, DARKPURPLE);
        EndDrawing();

        boid_update_neighbors(state);
        boid_state_update(state);
    }

    CloseWindow();
    boid_state_delete(state);
    return 0;
}