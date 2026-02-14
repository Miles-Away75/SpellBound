#include <unordered_map>
#include "raylib.h"
#include <string>
#include "Math.h"

enum AbilityType {
    Teleport,
    Dash
};
std::unordered_map<AbilityType, float> abilityCooldowns = {
    {Teleport, 20.0f},
    {Dash, 5.0f}
};

void UseAbility(AbilityType ability, Vector2 & playerPos, Vector2 & playerVel) {
    switch (ability) {
        case Teleport:
            playerPos = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
            break;
        case Dash:
            playerPos = {playerPos.x + playerVel.x * 40, playerPos.y + playerVel.y * 40};
            break;
    }
}
