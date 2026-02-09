#include "Game.h"

void Game::UpdateEndofLevel() {
    EventsEndofLevel();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawEndofLevel();
    EndDrawing();
}

void Game::DrawEndofLevel() {
    DrawText("Level Complete!", 225, 100, 40, BLACK);
    DrawText("Inventory Reward: ", 250, 200, 20, BLACK);
    spellSpritesheet.draw(spellSprites.at(levels[level].reward), {480, 210, 48, 48});
    DrawButton({300, 300, 200, 50}, "Next Level");
    DrawButton({250, 400, 300, 50}, "Change Spell Bindings");
}

void Game::EventsEndofLevel() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {300, 300, 200, 50})) {
        level = (level + 1) % levels.size();
        loadLevel();
        state = Playing;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {300, 400, 200, 50})) {
        state = Controls;
    }
}