////////////////////////////////////////////////////////////////////////////////
/// Raylib Physics Simulation Engine,                                        ///
/// Each Branch in this Project will be a different simulation               ///
/// the Master Branch contains a Demo of 2 Particles that are affected by    ///
/// Gravity in a Bounding Box.                                               ///
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdlib.h>

#include <raylib.h>
#include "typedef.h"

int main(void) {
    const u16 screenWidth = GetScreenWidth();
    const u16 screenHeight = GetScreenHeight();
    const char* screenTitle = "Physics Simulation";

    SetTargetFPS(120);
    InitWindow(screenWidth, screenHeight, screenTitle);
    ClearBackground(BLACK);

    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}
