#include <stdio.h>

#include <raylib.h>

int main(void) {
    const int width = 800, height = 600;
    const char* title = "Physics Engine";

    InitWindow(width, height, title);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Hello World!", 190, 200, 20, ORANGE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
