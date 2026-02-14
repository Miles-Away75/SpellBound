#include "Game.h"

void Game::DrawPowerUps() {
    for (PowerUp& powerUp : powerUps) {
        powerUpSpritesheet.draw(powerUpSprites.at(powerUp.type), powerUp.getHitbox());
    }
}
void Game::DrawCharacter() {
    // Draw the player character
    playerSpritesheet.draw(playerSprites[playerDirection][playerAnimFrame], {playerPos.x, playerPos.y, 42, 48});
    // Draw health bar
    playerHealthBar.Draw({15, 15, 100, 20});
    playerHealthBar.HandleHealthChange(health);
    playerHealthBar.Update();
    // Draw score
    DrawText(TextFormat("Score: %d", score), GetScreenWidth() - 150, 10, 20, BLACK);
}
void Game::DrawEnemies() {
    // Draw enemies
    for (Enemy &enemy : enemies) {
        enemy.Update(playerPos, activeSpells, enemyTexture);
    }
    if (ShouldSpawnEnemy()) {
        Vector2 spawnPos = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
        while (Distance(spawnPos, playerPos) < 100) { // Ensure enemies don't spawn too close to the player
            spawnPos = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
        }
        enemies.push_back(Enemy(spawnPos, "Enemy1"));
    }
}
void Game::DrawSpells() {
    for (Spell& spell : activeSpells) {
        spell.Draw(spellSpritesheet, spell.dir);
        spell.UpdatePosition(playerPos);
        if (!CheckCollisionRecs(spell.getHitbox(), {0, 0, ScreenWidth, ScreenHeight})) {
            // Remove spell if it goes off-screen
            spell = activeSpells.back();
            activeSpells.pop_back();
        }
    }
    // draw Spell cooldowns
    int i = 0;
    for (auto pair : bindedSpells) {
        float time = GetTime() - spellTimes[pair.first];
        float cooldown = spellInfos.at(pair.second).cooldown;
        if (time > cooldown) {
            time = cooldown;
        }
        DrawText(TextFormat("%c", pair.first),10, 50.0f + i * 20, 20, BLACK);
        DrawRectangleRec({25, 50.0f + i * 20, 40, 10}, GRAY);
        DrawRectangleRec({25, 50.0f + i * 20, 40 * (time / cooldown), 10}, (time >= cooldown) ? GREEN : RED);
        i++;
    }
    // Draw ability cooldowns
    for (auto pair : bindedAbilities) {
        float time = GetTime() - abilityTimes[pair.first];
        float cooldown = abilityCooldowns.at(pair.second);
        if (time > cooldown) {
            time = cooldown;
        }
        DrawText(TextFormat("%c", pair.first),10, 50.0f + i * 20, 20, BLACK);
        DrawRectangleRec({25, 50.0f + i * 20, 40, 10}, GRAY);
        DrawRectangleRec({25, 50.0f + i * 20, 40 * (time / cooldown), 10}, (time >= cooldown) ? GREEN : RED);
        i++;
    }
}