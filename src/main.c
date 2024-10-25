#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include <typedef.h>



int main(void) {
    i16 width = GetScreenWidth();
    i16 height = GetScreenHeight();
    const static char *title = "Physics Simulation";

    fprintf(stdout, "Project Initialising");

    SetTargetFPS(30);
    InitWindow(width, height, title);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}
