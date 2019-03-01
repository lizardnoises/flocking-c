#include "raylib.h"
#include "boid.h"
#include <stdlib.h>
#include <time.h>

void draw_boid(struct boid *b, float radius, Color color) {
    DrawCircleLines(b->position.x, b->position.y, radius, color);
    Vector2 direction = Vector2Divide(Vector2Normalize(b->velocity), 1.0f / (2.0f * radius));
    DrawLine(b->position.x,
             b->position.y,
             b->position.x + direction.x,
             b->position.y + direction.y,
             color);
    //DrawCircleLines(b->position.x, b->position.y, b->neighbors.radius, GRAY);
}

void draw_boids(struct boid_state *state) {
    for (unsigned i = 0; i < state->n; i++) {
        draw_boid(&(state->boids[i]), state->boid_size, DARKPURPLE);
    }
}

int main() {
    srand(time(NULL));

    const int screen_width = 1200;
    const int screen_height = 800;

    struct boid_parameters params = {
        .n = 100,
        .width = screen_width,
        .height = screen_height,
        .max_speed = 2.0f,
        .neighbor_radius = 150.0f,
        .x_separation = 1.0f,
        .x_cohesion = 0.003f,
        .x_alignment = 1.0f,
        .x_bounds = 0.002f,
        .boid_size = 5.0f
    };

    struct boid_state *state = boid_state_new(&params);

    InitWindow(screen_width, screen_height, "boids!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("boids!", state->width / 2 - 80, state->height / 2 - 20, 40, LIGHTGRAY);
        draw_boids(state);
        EndDrawing();

        boid_update_neighbors(state);
        boid_state_update(state);
    }

    CloseWindow();
    boid_state_delete(state);
    return 0;
}