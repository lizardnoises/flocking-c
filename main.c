#include "raylib.h"
#include "boids.h"
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
}

void draw_boids(struct boid_state *state, float radius) {
    for (unsigned i = 0; i < state->n; i++) {
        draw_boid(&(state->boids[i]), radius, DARKPURPLE);
    }
}

void update_boids(struct boid_state *state) {
    separation(state);
    cohesion(state);
    alignment(state);
    integrate(state);
}

int main() {
    srand(time(NULL));
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int n = 100;
    const float radius = 5.0f;
    const float mass = 1.0f;
    const float max_speed = 3.0f;
    const float max_force = 0.1f;
    const float fov_radius = 200.0f;

    struct boid boids[n];
    struct boid_state state;
    init_boids(&state,
               boids,
               n,
               screenWidth,
               screenHeight,
               mass,
               max_speed,
               max_force,
               fov_radius);

    InitWindow(screenWidth, screenHeight, "boids!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("boids!", 360, 280, 20, LIGHTGRAY);
        draw_boids(&state, radius);
        update_boids(&state);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}