#include "Game.h"



void Game::GetPlayerControls() {
    float currentPlayerAcceleration = playerAcceleration;
    if (hasSpeedUp) {currentPlayerAcceleration += 0.5f;}
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
        playerVel.x += Normalize({-currentPlayerAcceleration, -currentPlayerAcceleration}).x * currentPlayerAcceleration;
        playerVel.y += Normalize({-currentPlayerAcceleration, -currentPlayerAcceleration}).y * currentPlayerAcceleration;
        playerDirection = 225;
    }
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
        playerVel.x += Normalize({currentPlayerAcceleration, -currentPlayerAcceleration}).x * currentPlayerAcceleration;
        playerVel.y += Normalize({currentPlayerAcceleration, -currentPlayerAcceleration}).y * currentPlayerAcceleration;
        playerDirection = 315;
    }
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) {
        playerVel.x += Normalize({-currentPlayerAcceleration, currentPlayerAcceleration}).x * currentPlayerAcceleration;
        playerVel.y += Normalize({-currentPlayerAcceleration, currentPlayerAcceleration}).y * currentPlayerAcceleration;
        playerDirection = 135;
    }
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) {
        playerVel.x += Normalize({currentPlayerAcceleration, currentPlayerAcceleration}).x * currentPlayerAcceleration;
        playerVel.y += Normalize({currentPlayerAcceleration, currentPlayerAcceleration}).y * currentPlayerAcceleration;
        playerDirection = 45;
    }
    else if (IsKeyDown(KEY_W)) {
        playerVel.y -= currentPlayerAcceleration;
        playerDirection = 270;
    }
    else if (IsKeyDown(KEY_S)) {
        playerVel.y += currentPlayerAcceleration;
        playerDirection = 90;
    }
    else if (IsKeyDown(KEY_A)) {
        playerVel.x -= currentPlayerAcceleration;
        playerDirection = 180;
    }
    else if (IsKeyDown(KEY_D)) {
        playerVel.x += currentPlayerAcceleration;
        playerDirection = 0;
    }
    
}
void Game::GetPlayerSpellControls() {
    for (const auto& pair : bindedSpells) {
        if (IsKeyPressed(pair.first) && GetTime() - spellTimes[pair.first] > spellInfos.at(pair.second).cooldown) {
            activeSpells.push_back(Spell(pair.second, playerDirection, playerPos, Peaceful));
            spellTimes[pair.first] = GetTime();
            break;
        }
    }
}
void Game::GetPlayerAbilityControls() {
    for (const auto& pair : bindedAbilities) {
        if (IsKeyPressed(pair.first) && GetTime() - abilityTimes[pair.first] > abilityCooldowns.at(pair.second)) {
            UseAbility(pair.second, playerPos, playerVel);
            abilityTimes[pair.first] = GetTime();
            break;
        }
    }
}
void Game::EventsGame() {
    GetPlayerControls();
    GetPlayerSpellControls();
    GetPlayerAbilityControls();
    
    playerVel.x *= 0.8f; // Friction
    playerVel.y *= 0.8f; // Friction
    if (!RectInLevel({playerPos.x + playerVel.x, playerPos.y, 42, 48})) {
        playerVel.x = 0;
    }
    if (!RectInLevel({playerPos.x, playerPos.y + playerVel.y, 42, 48})) {
        playerVel.y = 0;
    }
    playerPos.x += playerVel.x;
    playerPos.y += playerVel.y;
}