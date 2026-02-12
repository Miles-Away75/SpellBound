#include "Game.h"
#include "Math.h"


void Game::UpdateGame() {
    
    EventsGame();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCharacter();
        DrawEnemies();
        DrawSpells();
    EndDrawing();

    CollisionsGame();
    if (state != Playing) return;
    if (enemies.size() == 0) { 
        state = EndofLevel;
        spellInventory.push_back(levels[level].reward);
        timeBetweenAttacks *= 0.8f; // increase difficulty by making enemies attack faster
    }
}

void Game::DrawCharacter() {
    // Draw the player character
    playerSpritesheet.draw(playerSprites.at(playerDirection), {playerPos.x, playerPos.y, 42, 48});
    
    DrawRectangleRec({15, 15, 100, 10}, GRAY);
    DrawRectangleRec({15, 15, 100 * ((float)health / 100), 10}, RED);
}
void Game::DrawEnemies() {
    // Draw enemies
    for (Enemy &enemy : enemies) {
        enemy.Update(playerPos, activeSpells, enemyTexture);
    }
}
void Game::DrawSpells() {
    for (Spell& spell : activeSpells) {
        spell.Draw(spellSpritesheet, spell.dir);
        spell.UpdatePosition(playerPos);
        if (spell.type == Teleport) {
            // Teleport spell is instant, remove after applying effect
            spell = activeSpells.back();
            activeSpells.pop_back();
        }
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
}
void Game::GetPlayerControls() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        state = Controls;
        return;
    }
    if (IsKeyDown(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        playerVel.y -= 0.5;
        playerDirection = 270;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_W) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        playerVel.y += 0.5;
        playerDirection = 90;
    } 
    else if (IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D)) {
        playerVel.x -= 0.5;
        playerDirection = 180;
    } 
    else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A)) {
        playerVel.x += 0.5;
        playerDirection = 0;
    } 
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D)) {
        Vector2 scheduled = {-0.5f, -0.5f};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 225;
    }
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A)) {
        Vector2 scheduled = {0.5f, -0.5f};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 315;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_D)) {
        Vector2 scheduled = {-0.5f, 0.5f};
        Normalize(scheduled);
        playerVel.x += scheduled.x/2;
        playerVel.y += scheduled.y/2;
        playerDirection = 135;
    } 
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_A)) {
        Vector2 scheduled = {0.5f, 0.5f};
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
}
void Game::EventsGame() {
    GetPlayerControls();
    playerPos.x += playerVel.x;
    playerPos.y += playerVel.y;
    playerVel.x *= 0.8f; // Friction
    playerVel.y *= 0.8f; // Friction
}
