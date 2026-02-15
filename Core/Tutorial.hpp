#include "Game.h"

void Game::UpdateTutorial() {
    if (IsKeyPressed(KEY_ENTER)) {
        state = Upgrading;
    }
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTutorial();
    
    EndDrawing();
}

void Game::DrawTutorial() {
    DrawText("Welcome to SpellBound!", ScreenWidth/2 - MeasureText("Welcome to SpellBound!", 40)/2, ScreenHeight/2 - 100, 40, BLACK);
    DrawText("Use WASD to move around", ScreenWidth/2 - MeasureText("Use WASD to move around", 20)/2, ScreenHeight/2 - 50, 20, DARKGRAY);
    DrawText("Press J, K, and L to cast spells", ScreenWidth/2 - MeasureText("Press J, K, and L to cast spells", 20)/2, ScreenHeight/2 - 20, 20, DARKGRAY);
    DrawText("Press R and F to use your abilities", ScreenWidth/2 - MeasureText("Press R and F to use your abilities", 20)/2, ScreenHeight/2 + 10, 20, DARKGRAY);
    DrawText("Defeat enemies to get power-ups and buy upgrades!", ScreenWidth/2 - MeasureText("Defeat enemies to get power-ups and buy upgrades!", 20)/2, ScreenHeight/2 + 40, 20, DARKGRAY);
    DrawText("Press ENTER to start playing!", ScreenWidth/2 - MeasureText("Press ENTER to start playing!", 30)/2, ScreenHeight/2 + 100, 30, BLACK);

    DrawText("J : Firaball\nK : Guard\nL : Shield\nR : Teleport\nF : Dash", 10, ScreenHeight - 150, 20, DARKGRAY);
}