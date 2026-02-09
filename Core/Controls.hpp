#include "Game.h"

// controls are spell bindings

void Game::UpdateControls() {
    EventsControls();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawControls();
    EndDrawing();
}
void Game::DrawControls() {
    int i = 0;
    for (auto pair : bindedSpells) {
        DrawText(TextFormat("%c: ", pair.first), 50, 50 + i * 40, 20, BLACK);
        spellSpritesheet.draw(spellSprites.at(pair.second), {100, 50.0f + i * 40, 48, 48});
        i++;
    }
    DrawButton({500, 500, 100, 50}, "Add New");
    std::string text = "Inventory: ";
    for (const auto& spell : spellInventory) {
        switch (spell) {
            case Fireball:
                text += "Fireball ";
                break;
            case Gaurd:
                text += "Gaurd ";
                break;
            case Shield:
                text += "Shield ";
                break;
        }
    }
    DrawText(text.c_str(), 50, 400, 20, BLACK);
}
void Game::EventsControls() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state = Playing;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {500, 500, 100, 50}) && spellInventory.size() > 0) {
        int key = 0;
        while (key == 0) {
            BeginDrawing();
            DrawText("Press a key to bind the spell to...", 300, 300, 20, BLACK);
            EndDrawing();
            key = GetKeyPressed();
        }
        bindedSpells[key] = spellInventory.back();
        spellTimes[key] = 0.0f;
        spellInventory.pop_back();
    }
}