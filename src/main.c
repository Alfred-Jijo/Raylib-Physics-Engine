////////////////////////////////////////////////////////////////////////////////
/// Raylib Physics Simulation Engine,                                        ///
/// Each Branch in this Project will be a different simulation               ///
/// the Master Branch contains a Demo of 2 Particles that are affected by    ///
/// Gravity in a Bounding Box.                                               ///
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdlib.h>

#include "typedef.h"

#include <raylib.h>
#include <time.h>

#include "raymath.h"

typedef Vector2 Vec2;
typedef struct Dot {
    Vec2 position;
    Vec2 velocity;
} dot_point;

int main(void) {
    srand(time(0));
    const double gravity_force = 9.81f;
    const double gravity_point_speed = 1.2f;
    const double speed_limit = 100.1f;

    const u16 screen_width = 1080;
    const u16 screen_height = 720;
    const char* screen_title = "Physics Simulation";

    InitWindow(screen_width, screen_height, screen_title);

    // Boolean variables
    u8 show_general_details = 1;
    u8 show_gravity_details = 1;
    u8 use_mouse_as_gravity_point = 0;

    // Gravity Calc vars
    Vec2 gravity_point = (Vector2) { screen_width/ 2, screen_height / 2 };
    Vec2 scaled_gravity_point;
    Vec2 move;
    double distance;
    double gravity_direction = 0f;

    // Dots vars
    size_t dot_quantity = 100;
    dot_point *dot_array = (dot_point *)malloc(dot_quantity * sizeof(dot_point));

    for (size_t i = 0; i < dot_quantity; i++) {
        dot_array[i].position = (Vec2) {
            (float)(rand() % screen_width) * 100,
            (float)(rand() % screen_height) * 100
        };
        dot_array[i].velocity = Vector2Zero;
    }

    SetTargetFPS(60);

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
            use_mouse_as_gravity_point = (uint8_t)(use_mouse_as_gravity_point == 0);
            gravity_point = Vector2{screen_width / 2, screen_height / 2};
        }
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
