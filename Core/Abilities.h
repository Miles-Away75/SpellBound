#include <unordered_map>
#include "raylib.h"
#include <string>
#include "Math.h"

enum AbilityType {
    Teleport,
    Dash,
    ABILITY_COUNT
};
std::unordered_map<AbilityType, float> abilityCooldowns = {
    {Teleport, 20.0f},
    {Dash, 2.0f}
};
std::unordered_map<AbilityType, Rectangle> abilitySprites = {
    {Dash, {0, 0, 66, 78}},
    {Teleport, {66, 0, 66, 78}}
};

void UseAbility(AbilityType ability, Vector2 & playerPos, Vector2 & playerVel) {
    switch (ability) {
        case Teleport:
            playerPos = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
            break;
        case Dash:
            playerPos = {playerPos.x + playerVel.x * 40, playerPos.y + playerVel.y * 40};
            break;
        default:
            break;
    }
}
