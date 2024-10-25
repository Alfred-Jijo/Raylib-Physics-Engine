#include <raylib.h>

#define COLOR_COUNT 23

int main(void) {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Physics Simulation");

    const Color colors[COLOR_COUNT] = {
        RAYWHITE, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN,
        SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN,
        LIGHTGRAY, GRAY, DARKGRAY, BLACK };

    Rectangle colorsRecs[COLOR_COUNT] = { 0 };

    for (int i = 0; i < COLOR_COUNT; i++) {
        colorsRecs[i].x = 10 + 30.0f
                        * (float)i + 2
                        * (float)i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }

    int colorSelected = 0;
    int colorSelectedPrev = colorSelected;
    int colorMouseHover = 0;
    float brushSize = 10.0f;
    bool mouseWasPressed = false;

    const Rectangle buttonSaveRec = { 750, 10, 40, 30 };
    bool buttonSaveMouseHover = false;
    bool showSaveMessage = false;
    int saveMessageCounter = 0;

    const RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    BeginTextureMode(target);
    ClearBackground(colors[0]);
    EndTextureMode();

    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        const Vector2 mousePos = GetMousePosition();

        if (IsKeyPressed(KEY_RIGHT)) colorSelected++;
        else if (IsKeyPressed(KEY_LEFT)) colorSelected--;

        if (colorSelected >= COLOR_COUNT) colorSelected = COLOR_COUNT - 1;
        else if (colorSelected < 0) colorSelected = 0;

        for (int i = 0; i < COLOR_COUNT; i++) {
            if (CheckCollisionPointRec(mousePos, colorsRecs[i])) {
                colorMouseHover = i;
                break;
            } else colorMouseHover = -1;
        }

        if ((colorMouseHover >= 0) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            colorSelected = colorMouseHover;
            colorSelectedPrev = colorSelected;
        }

        brushSize += GetMouseWheelMove() * 5;
        if (brushSize < 2) brushSize = 2;
        if (brushSize > 50) brushSize = 50;

        if (IsKeyPressed(KEY_C)) {
            BeginTextureMode(target);
            ClearBackground(colors[0]);
            EndTextureMode();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || (GetGestureDetected() == GESTURE_DRAG)) {
            BeginTextureMode(target);
            if (mousePos.y > 50) DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorSelected]);
            EndTextureMode();
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            if (!mouseWasPressed) {
                colorSelectedPrev = colorSelected;
                colorSelected = 0;
            }

            mouseWasPressed = true;

            BeginTextureMode(target);
            if (mousePos.y > 50) DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[0]);
            EndTextureMode();
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && mouseWasPressed) {
            colorSelected = colorSelectedPrev;
            mouseWasPressed = false;
        }

        if (CheckCollisionPointRec(mousePos, buttonSaveRec)) buttonSaveMouseHover = true;
        else buttonSaveMouseHover = false;

        if ((buttonSaveMouseHover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || IsKeyPressed(KEY_S)) {
            Image image = LoadImageFromTexture(target.texture);
            ImageFlipVertical(&image);
            ExportImage(image, "my_amazing_texture_painting.png");
            UnloadImage(image);
            showSaveMessage = true;
        }

        if (showSaveMessage) {
            saveMessageCounter++;
            if (saveMessageCounter > 240) {
                showSaveMessage = false;
                saveMessageCounter = 0;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureRec(target.texture, (Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2) { 0, 0 }, WHITE);

        if (mousePos.y > 50) {
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) DrawCircleLines((int)mousePos.x, (int)mousePos.y, brushSize, GRAY);
            else DrawCircle(GetMouseX(), GetMouseY(), brushSize, colors[colorSelected]);
        }

        DrawRectangle(0, 0, GetScreenWidth(), 50, RAYWHITE);
        DrawLine(0, 50, GetScreenWidth(), 50, LIGHTGRAY);

        for (int i = 0; i < COLOR_COUNT; i++) DrawRectangleRec(colorsRecs[i], colors[i]);
        DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

        if (colorMouseHover >= 0) DrawRectangleRec(colorsRecs[colorMouseHover], Fade(WHITE, 0.6f));

        DrawRectangleLinesEx((Rectangle){ colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
                             colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4 }, 2, BLACK);

        DrawRectangleLinesEx(buttonSaveRec, 2, buttonSaveMouseHover ? RED : BLACK);
        DrawText("SAVE!", 755, 20, 10, buttonSaveMouseHover ? RED : BLACK);

        if (showSaveMessage) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
            DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
            DrawText("IMAGE SAVED:  stupid looking picture.png", 150, 180, 20, RAYWHITE);
        }

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
