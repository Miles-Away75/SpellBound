#include "Game.h"




// Upgrading are spell bindings
Rectangle card1 = {50, 200, 200, 100};
Rectangle card2 = {300, 200, 200, 100};
Rectangle card3 = {550, 200, 200, 100};

void Game::UpdateUpgrading() {
    EventsUpgrading();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawUpgrading();
    EndDrawing();
}
void Game::DrawUpgrading() {
    DrawRectangleRec(card1, DARKBLUE);
    DrawRectangleRec(card2, DARKBLUE);
    DrawRectangleRec(card3, DARKBLUE);
    for (int i = 0; i < 3; i++) {
        UpgradeType upgrade = currentUpgrades[i];
        Rectangle card = ((std::vector<Rectangle>){card1, card2, card3})[i];
        switch (upgrade) {
            case SpellUpgrade:
                DrawText("Spell Upgrade", card.x + 20, card.y + 40, 20, WHITE);
                break;
            case AbilityUpgrade:
                DrawText("Ability Upgrade", card.x + 20, card.y + 40, 20, WHITE);
                break;
            case UpMaxHealth:
                DrawText("Increase Max Health", card.x + 20, card.y + 40, 20, WHITE);
                break;
            
        }
    }
}
void Game::EventsUpgrading() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < 3; i++) {
            Rectangle card = ((std::vector<Rectangle>){card1, card2, card3})[i];
            if (CheckCollisionPointRec(mousePos, card)) {
                UpgradeType upgrade = currentUpgrades[i];
                int key;
                SpellType newSpell;
                AbilityType newAbility;
                switch (upgrade) {
                    case SpellUpgrade:
                        // Add a random spell to the inventory
                        key = 0;
                        newSpell = (SpellType)random(0, SpellType::SPELL_COUNT);
                        while (!key) {
                            BeginDrawing();
                            ClearBackground(RED);
                            DrawText("Press a key to bind the new spell to", 150, 200, 20, WHITE);
                            spellSpritesheet.draw(spellSprites.at(newSpell), {150, 250, 48, 48});
                            EndDrawing();
                            key = GetKeyPressed();
                        }
                        bindedSpells[key] = newSpell;
                        break;
                    case AbilityUpgrade:
                        // Add a random ability to the inventory
                        key = 0;
                        newAbility = (AbilityType)random(0, AbilityType::ABILITY_COUNT);
                        while (!key) {
                            BeginDrawing();
                            ClearBackground(RED);
                            DrawText("Press a key to bind the new ability to", 150, 200, 20, WHITE);
                            // Assuming you have a way to draw ability icons similar to spells
                            DrawText((newAbility == Teleport) ? "Teleport" : "Dash", 150, 250, 20, WHITE);
                            EndDrawing();
                            key = GetKeyPressed();
                        }
                        bindedAbilities[key] = newAbility;
                        break;
                    case UpMaxHealth:
                        maxHealth += 20;
                        break;
                }
                state = Playing;
                return;
            }
        }
    }
}