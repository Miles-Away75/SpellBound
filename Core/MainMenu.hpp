#include "Game.h"

void Game::UpdateMainMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("SpellBound", 300, 100, 40, BLACK);
    Rectangle PlayButton = {300, 200, 200, 50};
    Rectangle QuitButton = {300, 300, 200, 50};
    DrawButton(PlayButton, "Play");
    DrawButton(QuitButton, "Quit");
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), PlayButton)) {
        state = Tutorial;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), QuitButton)) {
        isRunning = false;
    }
    EndDrawing();
}