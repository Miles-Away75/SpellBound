#include "Game.h"



void Game::GetPlayerControls() {
    if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) {
        playerVel.x += Normalize({-playerAcceleration, -playerAcceleration}).x * playerAcceleration;
        playerVel.y += Normalize({-playerAcceleration, -playerAcceleration}).y * playerAcceleration;
        playerDirection = 225;
    }
    else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) {
        playerVel.x += Normalize({playerAcceleration, -playerAcceleration}).x * playerAcceleration;
        playerVel.y += Normalize({playerAcceleration, -playerAcceleration}).y * playerAcceleration;
        playerDirection = 315;
    }
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) {
        playerVel.x += Normalize({-playerAcceleration, playerAcceleration}).x * playerAcceleration;
        playerVel.y += Normalize({-playerAcceleration, playerAcceleration}).y * playerAcceleration;
        playerDirection = 135;
    }
    else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D)) {
        playerVel.x += Normalize({playerAcceleration, playerAcceleration}).x * playerAcceleration;
        playerVel.y += Normalize({playerAcceleration, playerAcceleration}).y * playerAcceleration;
        playerDirection = 45;
    }
    else if (IsKeyDown(KEY_W)) {
        playerVel.y -= playerAcceleration;
        playerDirection = 270;
    }
    else if (IsKeyDown(KEY_S)) {
        playerVel.y += playerAcceleration;
        playerDirection = 90;
    }
    else if (IsKeyDown(KEY_A)) {
        playerVel.x -= playerAcceleration;
        playerDirection = 180;
    }
    else if (IsKeyDown(KEY_D)) {
        playerVel.x += playerAcceleration;
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