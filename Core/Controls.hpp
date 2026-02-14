#include "Game.h"

// controls are spell bindings

const Rectangle AddNewButton = {400, 500, 100, 50};
const Rectangle AddAbilityButton = {550, 500, 150, 50};
const Rectangle HomeButton = {200, 500, 100, 50};

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
        DrawButton({200, 50.0f + i * 40, 100, 30}, "Delete");
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {200, 50.0f + i * 40, 100, 30})) {
            spellInventory.push_back(pair.second);
            bindedSpells.erase(pair.first);
            spellTimes.erase(pair.first);
            break;
        }
        i++;
    }
    for (auto pair : bindedAbilities) {
        DrawText(TextFormat("%c: ", pair.first), 50, 50 + i * 40, 20, BLACK);
        switch (pair.second) {
            case Teleport:
                DrawText("Teleport", 100, 50.0f + i * 40, 20, BLACK);
                break;
            case Dash:
                DrawText("Dash", 100, 50.0f + i * 40, 20, BLACK);
                break;
        }
        DrawButton({200, 50.0f + i * 40, 100, 30}, "Delete");
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), {200, 50.0f + i * 40, 100, 30})) {
            abilityInventory.push_back(pair.second);
            bindedAbilities.erase(pair.first);
            abilityTimes.erase(pair.first);
            break;
        }
        i++;
    }
    DrawButton(AddNewButton, "Add New Spell");
    DrawButton(AddAbilityButton, "Add New Ability");
    DrawButton(HomeButton, "Home");
    std::string text = "Spells: ";
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
            case Thunder:
                text += "Thunder ";
                break;         
        }
    }
    DrawText(text.c_str(), 50, 400, 20, BLACK);
     text = "Abilities: ";
    for (const auto& ability : abilityInventory) {
        switch (ability) {
            case Teleport:
                text += "Teleport ";
                break;
            case Dash:
                text += "Dash ";
                break;        
        }
    }
    DrawText(text.c_str(), 50, 450, 20, BLACK);
}
void Game::EventsControls() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state = Playing;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), AddNewButton) && spellInventory.size() > 0) {
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
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), AddAbilityButton) && abilityInventory.size() > 0) {
        int key = 0;
        while (key == 0) {
            BeginDrawing();
            DrawText("Press a key to bind the ability to...", 300, 300, 20, BLACK);
            EndDrawing();
            key = GetKeyPressed();
        }
        bindedAbilities[key] = abilityInventory.back();
        abilityTimes[key] = 0.0f;
        abilityInventory.pop_back();
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), HomeButton)) {
        state = Playing;
    } 
}