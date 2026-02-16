#include "Game.h"



Upgrade Game::generateUpgrade(UpgradeType type) {
    Upgrade upgrade;
    while (true) {
        upgrade.type = type;
        std::cout << "Generating upgrade of type " << type << "\n";
        upgrade.price = upgradePrices.at(type);
        if (type == SpellUpgrade) {
            upgrade.spellUpgrade = (SpellType)GetRandomValue(0, SpellType::SPELL_COUNT - 1);
        } else if (type == AbilityUpgrade) {
            upgrade.abilityUpgrade = (AbilityType)GetRandomValue(0, AbilityType::ABILITY_COUNT - 1);
        }
        if (!contains(currentUpgrades, upgrade)) {
            return upgrade;
        }
    }
    return upgrade;
}

Rectangle startButton = {300, 500, 200, 50};
Rectangle shopButton = {350, 300, 100, 50};

// Upgrading are spell bindings
Rectangle card1 = {50, 200, 200, 100};
Rectangle card2 = {300, 200, 200, 100};
Rectangle card3 = {550, 200, 200, 100};

Rectangle card1Button = {50, 450, 200, 50};
Rectangle card2Button = {300, 450, 200, 50};
Rectangle card3Button = {550, 450, 200, 50};

Rectangle rerollButton = {325, 100, 150, 50};

void Game::UpdateUpgrading() {
    EventsUpgrading();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawUpgrading();
    EndDrawing();
}
void Game::DrawUpgrading() {
    // draw Spells and abilities
    int i = 0;
    for (auto pair : bindedSpells) {
        DrawText(TextFormat("%c", pair.first),10, 10.0f + i * 50, 20, BLACK);
        spellSpritesheet.draw(spellSprites.at(pair.second), {50, 20.0f + i * 50, 40, 40});
        i++;
    }
    i = 0;
    for (auto pair : bindedAbilities) {
        DrawText(TextFormat("%c", pair.first),100, 20.0f + i * 50, 20, BLACK);
        abilitySpritesheet.draw(abilitySprites.at(pair.second), {140, 20.0f + i * 50 , 35, 40});
        i++;
    }
    DrawButton(startButton, "Start Round");
    DrawButton(shopButton, "Shop");
    coin.draw({700, 10}, 0.5f);
    DrawText(TextFormat("%d", coins), 750, 10, 20, BLACK);
}
void Game::EventsUpgrading() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), startButton)) {
        state = Playing;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), shopButton)) {
        state = PickingUpgrade;
        rerollsLeft = 3;
        GetRandomUpgrades();
    }
}
void Game::UpdatePickingUpgrade() {
    EventsPickingUpgrade();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawPickingUpgrade();
    EndDrawing();
}
void Game::DrawPickingUpgrade() {
    DrawRectangleRec(card1, DARKBLUE);
    DrawRectangleRec(card2, DARKBLUE);
    DrawRectangleRec(card3, DARKBLUE);

    DrawRectangleRec(card1Button, GREEN);
    DrawRectangleRec(card2Button, GREEN);
    DrawRectangleRec(card3Button, GREEN);

    DrawButton(rerollButton, TextFormat("Rerolls : %d", rerollsLeft));

    coin.draw({700, 10}, 0.5f);
    DrawText(TextFormat("%d", coins), 750, 10, 20, BLACK);
    for (int i = 0; i < 3; i++) {
        Upgrade upgrade = currentUpgrades[i];
        Rectangle card = ((std::vector<Rectangle>){card1, card2, card3})[i];
        Rectangle button = ((std::vector<Rectangle>){card1Button, card2Button, card3Button})[i];
        DrawButton(button, "Buy", (coins >= upgrade.price) ? GREEN : RED);
        coin.draw({button.x + 78, button.y + 70}, 0.5f);
        DrawText(TextFormat("%d", upgrade.price), button.x + 100, button.y + 70, 20, BLACK);
        
        switch (upgrade.type) {
            case SpellUpgrade:
                spellSpritesheet.draw(spellSprites.at(upgrade.spellUpgrade), {card.x + 100, card.y + 50, 48, 48});
                break;
            case AbilityUpgrade:
                abilitySpritesheet.draw(abilitySprites.at(upgrade.abilityUpgrade), {card.x + 100, card.y + 50, 44, 52});
                break;
            default:
                break;
            
        }
    }
}
void Game::EventsPickingUpgrade() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, rerollButton) && rerollsLeft > 0) {
            GetRandomUpgrades();
            rerollsLeft--;
            return;
        }
        for (int i = 0; i < 3; i++) {
            Rectangle button = ((std::vector<Rectangle>){card1Button, card2Button, card3Button})[i];
            if (CheckCollisionPointRec(mousePos, button) && coins >= currentUpgrades[i].price) {
                coins -= currentUpgrades[i].price;
                Upgrade upgrade = currentUpgrades[i];
                int key;
                SpellType newSpell;
                AbilityType newAbility;
                switch (upgrade.type) {
                    case SpellUpgrade:
                        // Add a random spell to the inventory
                        key = 0;
                        newSpell = upgrade.spellUpgrade;
                        while (!key) {
                            BeginDrawing();
                            ClearBackground(RED);
                            DrawText("Press a key to bind the new spell to", 150, 200, 20, WHITE);
                            spellSpritesheet.draw(spellSprites.at(newSpell), {150, 300, 48, 48});
                            EndDrawing();
                            key = GetKeyPressed();
                        }
                        bindedSpells[key] = newSpell;
                        break;
                    case AbilityUpgrade:
                        // Add a random ability to the inventory
                        key = 0;
                        newAbility = upgrade.abilityUpgrade;
                        while (!key) {
                            BeginDrawing();
                            ClearBackground(RED);
                            DrawText("Press a key to bind the new ability to", 150, 200, 20, WHITE);

                            abilitySpritesheet.draw(abilitySprites.at(newAbility), {150, 300, 44, 52});
                            EndDrawing();
                            key = GetKeyPressed();
                        }
                        bindedAbilities[key] = newAbility;
                        break;
                    default:
                        break;
                }
                state = Upgrading;
                return;
            }
        }
    }
}