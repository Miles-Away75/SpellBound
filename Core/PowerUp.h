#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

enum PowerUpType {
    Health,
    Upgrade,
    DamageUp,
    SpeedUp,
    None
};

std::unordered_map<PowerUpType, Rectangle> powerUpSprites = {
    {Upgrade, {0, 0, 48, 42}},
    {Health, {48, 0, 48, 42}},
    {DamageUp, {0, 42, 48, 42}},
    {SpeedUp, {48, 42, 48, 42}}
};

class PowerUp {
    public:
        PowerUpType type;
        Vector2 pos;
        PowerUp(PowerUpType n_type, Vector2 n_pos) : type(n_type), pos(n_pos) {}
        Rectangle getHitbox() {
            return {pos.x, pos.y, 48, 42};
        }
};
