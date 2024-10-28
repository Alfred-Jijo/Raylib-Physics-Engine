////////////////////////////////////////////////////////////////////////////////
/// Raylib Physics Simulation Engine,                                        ///
/// Each Branch in this Project will be a different simulation               ///
/// the Master Branch contains a Demo of 2 Particles that are affected by    ///
/// Gravity in a Bounding Box.                                               ///
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "typedef.h"

#include "raylib.h"
#include "raymath.h"

typedef struct Dot {
    Vector2 position;
    Vector2 velocity;
} dot_point;

int main(void) {
    const double gravity_force = 5000000;
    const double gravity_point_speed = 50;
    const double speed_limit = 7500;

    const u16 screen_width = 1440;
    const u16 screen_height = 960;
    const char* screen_title = "Physics Simulation";

    InitWindow(screen_width, screen_height, screen_title);

    // Boolean variables
    u8 show_general_details = 1;
    u8 show_gravity_details = 1;
    u8 use_mouse_as_gravity_point = 0;
    u8 use_dark_mode = 0;

    // Gravity Calc vars
    Vector2 gravity_point = (Vector2) { screen_width/ 2, screen_height / 2 };
    Vector2 scaled_gravity_point;
    Vector2 move;
    double distance;
    double gravity_direction = 0;

    // Dots vars
    size_t dot_quantity = 2000;
    dot_point *dot_array = (dot_point *)malloc(dot_quantity * sizeof(dot_point));

    for (size_t i = 0; i < dot_quantity; i++) {
        dot_array[i].position = (Vector2) {
            (float)(rand() % screen_width) * 100,
            (float)(rand() % screen_height) * 100
        };
        dot_array[i].velocity = (Vector2) {
                                    .x = 0,
                                    .y = 0
                                };
    }

    SetTargetFPS(130);

    // Main Sim Loop
    while (!WindowShouldClose()) {
        // Toggle Bool vars
        if (IsKeyReleased(KEY_INSERT)) {
            show_general_details = (u8)(!show_general_details);
        }
        if (IsKeyReleased(KEY_DELETE)) {
            show_gravity_details = (u8)(!show_gravity_details);
        }
        // Toggles the gravity mode - -1 to 0 to 1 to -1
        if (IsKeyReleased(KEY_R)) {
            gravity_direction = (gravity_direction == 0) ? 1 : ((gravity_direction == 1) ? -1 : 0);
        }
        /*       Same as:
        if (gravityDirection == 0) {
            gravityDirection = 1;
        } else if (gravityDirection == 1) {
            gravityDirection = -1;
        } else {
            gravityDirection = 0;
        }
        */

        // Toggle if the gravity point is based on the mouse position or not
        if (IsKeyReleased(KEY_P)) {
            use_mouse_as_gravity_point = (u8)(use_mouse_as_gravity_point == 0);
            gravity_point = (Vector2) {screen_width / 2, screen_height / 2};
        }

        if (IsKeyReleased(KEY_K)) {
            use_dark_mode = (u8)(use_dark_mode == 0);
        }

        // Update Loop
        if (use_mouse_as_gravity_point) {
            gravity_point = GetMousePosition();
        }
        else {
            // Horizontal movement
            if (IsKeyDown(KEY_A)) {
                gravity_point.x -= gravity_point_speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_D)) {
                gravity_point.x += gravity_point_speed * GetFrameTime();
            }
            // Vertical movement
            if (IsKeyDown(KEY_W)) {
                gravity_point.y -= gravity_point_speed * GetFrameTime();
            }
            if (IsKeyDown(KEY_S)) {
                gravity_point.y += gravity_point_speed * GetFrameTime();
            }
            // Go back to default position
            if (IsKeyDown(KEY_H)) {
                gravity_point.x = screen_width / 2;
            }
        }

        for (size_t i = 0; i < dot_quantity; i++) {
            scaled_gravity_point = Vector2Scale(gravity_point, 100);
            distance = Vector2Distance(scaled_gravity_point, dot_array[i].position);

            if (!(distance < 99
                  && distance > -99)) {
                move = Vector2MoveTowards(dot_array[i].position, scaled_gravity_point, 1);
                // Now here's where it gets funky
                dot_array[i].velocity = Vector2Add(
                    Vector2Scale(
                        Vector2Normalize(
                            Vector2Subtract(
                                move,
                                dot_array[i].position)),
                        (GetFrameTime() * gravity_force * gravity_direction) / (distance / 2)),
                    dot_array[i].velocity);

                if (Vector2Length(dot_array[i].velocity) > speed_limit) {
                    dot_array[i].velocity = Vector2Scale(Vector2Normalize(dot_array[i].velocity), speed_limit);
                }
            }
        }

        // Update Position
        for (size_t i = 0; i < dot_quantity; i++) {
            dot_array[i].position = Vector2Add(dot_array[i].position, Vector2Scale(dot_array[i].velocity, GetFrameTime()));
        }

        // Drawing time
        BeginDrawing();
        if (use_dark_mode) {
            ClearBackground(BLACK);
            for (size_t i = 0; i < dot_quantity; i++) {
                DrawCircleV(Vector2Scale(dot_array[i].position, 0.01), 2.0f, (Color) {(unsigned char)(Vector2Length
                (dot_array[i].velocity) * 200 / speed_limit + 55), 0, 0, 255});
            }
            DrawText("DARK MODE: ON", screen_width - 140, 5, 18, ORANGE);
        }
        else {
            ClearBackground(RAYWHITE);
            for (size_t i = 0; i < dot_quantity; i++) {
                DrawCircleV(Vector2Scale(dot_array[i].position, 0.01), 2.0f, BLACK);
            }
        }

        DrawCircleV(gravity_point, 2.0f, GRAY);
        if (show_general_details) {
            // General details
            char fps_string[1000];
            snprintf(fps_string, sizeof(fps_string), "FPS: %d", GetFPS());

            char dot_quantity_string[1000];
            snprintf(dot_quantity_string, sizeof(dot_quantity_string), "DOTS: %d", dot_quantity);

            DrawText(fps_string,5, 5, 18, ORANGE);
            DrawText(dot_quantity_string,5, 25, 18, ORANGE);
        }

        if (show_gravity_details) {
            char grav_force_string[1000];
            char grav_mode_string[1000];
            char grav_pos_string[1000];
            char grav_x[1000];
            char grav_y[1000];
            char grav_point_speed_string[1000];

            snprintf(grav_force_string, sizeof(grav_force_string), "GRAV FORCE: %d", gravity_force);
            snprintf(grav_mode_string, sizeof(grav_mode_string), "GRAV. MODE: %s",
                     (gravity_direction == 0) ? "DISABLED" :
                     ((gravity_direction == 1) ? "NORMAL" : "REVERSED"));
            snprintf(grav_pos_string, sizeof(grav_pos_string), "GRAV POSITION: %d", gravity_point);
            snprintf(grav_x, sizeof(grav_x), "X: %d", gravity_point.x);
            snprintf(grav_y, sizeof(grav_y), "Y: %d", gravity_point.y);
            snprintf(grav_point_speed_string, sizeof(grav_point_speed_string), "GRAV POINT SPEED: %d", gravity_point_speed);

            DrawText(grav_force_string, 5, 55, 18, ORANGE);
            DrawText(grav_mode_string, 5, 75, 18, ORANGE);
            DrawText(grav_pos_string, 5, 95, 18, ORANGE);
            DrawText(grav_x, 5, 115, 18, ORANGE);
            DrawText(grav_y, 5, 135, 18, ORANGE);

            if(!use_mouse_as_gravity_point) {
                DrawText(grav_point_speed_string, 5, 155, 18, ORANGE);
            }
        }
        // KEYS
        DrawText(
        "INSERT - Info. 1 Toggle | DELETE - Info. 2 Toggle | R - Grav. Mode Toggle | P - Grav. Point Toggle | K - Toggle Dark Mode",
            5,
            screen_height - 20,
            20,
            ORANGE
        );
        EndDrawing();
    }

    free(dot_array);
    CloseWindow();
    return EXIT_SUCCESS;
}
