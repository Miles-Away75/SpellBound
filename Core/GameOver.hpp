#include "Game.h"

const Rectangle GameOverButton = {275, 400, 250, 50};

void Game::UpdateGameOver() {
    BeginDrawing();
    ClearBackground(RED);
    DrawGameOver();
    EndDrawing();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), GameOverButton)) {
        state = Playing;
    }
}

void Game::DrawGameOver() {
    std::string text = "Game Over! You reached level " ;
    DrawText("Game Over", 300, 200, 40, BLACK);
    DrawButton(GameOverButton, "Return to Main Menu");
}