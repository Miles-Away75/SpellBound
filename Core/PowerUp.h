#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>

enum PowerUpType {
    Health,
    DamageUp,
    SpeedUp,
    None
};

std::unordered_map<PowerUpType, Rectangle> powerUpSprites = {
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
            return {pos.x, pos.y, 24, 21};
        }
};
