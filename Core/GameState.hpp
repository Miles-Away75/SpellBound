#include "Game.h"
#include "Math.h"

void Game::GetRandomUpgrades() {
    currentUpgrades.clear();
    for (int i = 0; i < 3; i++) {
        currentUpgrades.push_back((UpgradeType)random(0, UpgradeType::UPGRADE_COUNT));
    }
}

bool Game::ShouldSpawnEnemy() {
    if (GetTime() - timeSinceLastSpawn > timeBetweenSpawns) {
        if (GetRandomValue(0, 100) < 25) { // 25% chance to spawn an enemy every time the timer runs out
            timeSinceLastSpawn = GetTime();
            return true;
        }
        return false;
    }
    return false;
}
PowerUpType Game::GetRandomPowerUp() {
    int r = GetRandomValue(0, 100);
    if (r < 10) {
        return Health;
    }
    if (r < 20) {
        return DamageUp;
    }
    if (r < 30) {
        return SpeedUp;
    }
    if (r < 35) {
        return Upgrade;
    }
    return None;
}

void Game::UpdateGame() {
    
    EventsGame();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCharacter();
        DrawPowerUps();
        DrawEnemies();
        DrawSpells();
        
    EndDrawing();

    CollisionsGame();
    if (state != Playing) return;
}

void Game::DrawPowerUps() {
    for (PowerUp& powerUp : powerUps) {
        powerUpSpritesheet.draw(powerUpSprites.at(powerUp.type), powerUp.getHitbox());
    }
}

void Game::DrawCharacter() {
    // Draw the player character

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
        
        timeSinceFrameStart += GetFrameTime();
        if (timeSinceFrameStart > 1.0f / playerFPS) {
            playerAnimFrame = (playerAnimFrame + 1) % playerSprites[playerDirection].size();
            timeSinceFrameStart = 0.0f;
        }
    } 
    else {
        playerAnimFrame = 0;
    }
    playerSpritesheet.draw(playerSprites[playerDirection][playerAnimFrame], {playerPos.x, playerPos.y, 42, 48});

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
void Game::GetPlayerControls() {
    if (IsKeyDown(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        playerVel.y -= playerAcceleration;
        playerDirection = 270;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_W) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        playerVel.y += playerAcceleration;
        playerDirection = 90;
    } 
    else if (IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D)) {
        playerVel.x -= playerAcceleration;
        playerDirection = 180;
    } 
    else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A)) {
        playerVel.x += playerAcceleration;
        playerDirection = 0;
    } 
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D)) {
        Vector2 scheduled = {-playerAcceleration, -playerAcceleration};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 225;
    }
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A)) {
        Vector2 scheduled = {playerAcceleration, -playerAcceleration};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 315;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_D)) {
        Vector2 scheduled = {-playerAcceleration, playerAcceleration};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 135;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_A)) {
        Vector2 scheduled = {playerAcceleration, playerAcceleration};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 45;
    }
    // take spell inputs
    for (const auto& pair : bindedSpells) {

        if (IsKeyPressed(pair.first) && GetTime() - spellTimes[pair.first] > spellInfos.at(pair.second).cooldown) {
            activeSpells.push_back(Spell(pair.second, playerDirection, playerPos, Peaceful));
            spellTimes[pair.first] = GetTime();
            break;
        }
    }
    for (const auto& pair : bindedAbilities) {

        abilityCooldowns.at(pair.second); // Check if ability exists

        if (IsKeyPressed(pair.first) && GetTime() - abilityTimes[pair.first] > abilityCooldowns.at(pair.second)) {
            UseAbility(pair.second, playerPos, playerVel);
            abilityTimes[pair.first] = GetTime();
            break;
        }
    }
}
void Game::EventsGame() {
    GetPlayerControls();
    playerPos.x += playerVel.x;
    playerPos.y += playerVel.y;
    playerVel.x *= 0.8f; // Friction
    playerVel.y *= 0.8f; // Friction
}
