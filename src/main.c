#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#include <typedef.h>

#define COLOUR_COUNT 26

int main(void) {
    u16 width = GetScreenWidth();
    u16 height = GetScreenHeight();
    const static char *title = "Physics Simulation";

    fprintf(stdout, "Project Initialising");

    Color colours[COLOUR_COUNT] = {
        LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON,
        GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET,
        DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, BLANK, MAGENTA, RAYWHITE
    };

    Rectangle colourRects[COLOUR_COUNT] = {0};

    for (u8 i = 0; i < COLOUR_COUNT; i++) {
        colourRects[i].x = 10 + 30.f*i + 2*i;
        colourRects[i].y = 10;
        colourRects[i].width = 30;
        colourRects[i].height = 30;
    }

    int colorSelected = 0;
    int colorSelectedPrev = colorSelected;
    int colorMouseHover = 0;
    float brushSize = 20.0f;
    bool mouseWasPressed = false;

    Rectangle buttonSaveRec = { 750, 10, 40, 30 };
    bool buttonSaveMouseHover = false;
    bool showSaveMessage = false;
    int saveMessageCounter = 0;

    RenderTexture2D canvas = LoadRenderTexture(width, height);

    BeginTextureMode(canvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();

    SetTargetFPS(60);
    InitWindow(width, height, title);
    while (!WindowShouldClose()) {
        BeginDrawing();
            f32 mouseCircleRadius = 2.0f;
            DrawCircle(GetMousePosition().x,GetMousePosition().y,mouseCircleRadius,WHITE);
        EndDrawing();
    }
    CloseWindow();
    return EXIT_SUCCESS;
}
