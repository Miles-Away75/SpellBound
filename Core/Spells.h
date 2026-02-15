#include "raylib.h"
#include "SmartTexture.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "Math.h"


enum SpellType {
    Fireball,
    Gaurd,
    Shield,
    Thunder,
    SPELL_COUNT
};
enum Mode {
    Peaceful,
    Opposing,
};
enum MovementType {
    Stationary,
    Line,
    FollowPlayer,
};

struct SpellInfo {
    int damage;
    int piercing;
    float cooldown;
    float speed;
    MovementType movementType = Line;
};

const std::unordered_map<SpellType, SpellInfo> spellInfos = {// damage, piercing, cooldown, speed (px/s)
    {Fireball, {10, 0, 1.0f, 200.0f, Line}}, 
    {Gaurd, {0, 0, 1.0f, 200.0f, Line}},
    {Shield, {0, 0, 5.0f, 0.0f, Stationary}},
    {Thunder, {10, 0, 5.0, 400, Line}},
};
const std::unordered_map<SpellType, Rectangle> spellSprites = { // Type : Sprite
    {Fireball, {0, 0, 48, 48}},
    {Gaurd, {48, 0, 48, 48}},
    {Shield, {0, 48, 48, 48}},
    {Thunder, {48, 48, 48, 48}}
};
const std::unordered_map<std::string, float> angles = {
    {"Up", 270},
    {"Down", 90},
    {"Left", 180},
    {"Right", 0},
    {"UpLeft", 225},
    {"UpRight", 315},
    {"DownLeft", 135},
    {"DownRight", 45}
};


struct Spell {
    SpellType type;
    SpellInfo info;
    Vector2 pos;
    float dir;
    Mode mode;
    Spell(SpellType type, float n_dir, Vector2 n_pos, Mode n_mode, MovementType movement = Line) : type(type), info(spellInfos.at(type)),  pos(n_pos),dir(n_dir), mode(n_mode) {
        if (movement != spellInfos.at(type).movementType) {
            info.movementType = movement;
        }
    }

    bool IsProtectingType() {
        return type == Gaurd || type == Shield;
    }
    void Draw(Spritesheet& spritesheet, float dir) {
        Rectangle spriteRect = spellSprites.at(type);   
        spritesheet.draw(spriteRect, {pos.x, pos.y, 48, 48}, dir);
    }
    void UpdatePosition(Vector2 & playerPos) {
        if (info.movementType == Stationary) return;
        if (info.movementType == FollowPlayer) {
            Vector2 direction = {playerPos.x - pos.x, playerPos.y - pos.y};
            direction = Normalize(direction);
            pos.x += direction.x * info.speed * GetFrameTime();
            pos.y += direction.y * info.speed * GetFrameTime();
            return;
        }

        Vector2 vel = {std::cos(dir * (3.14/180)) * info.speed, std::sin(dir * (3.14/180)) * info.speed};
        pos.x += vel.x * GetFrameTime();
        pos.y += vel.y * GetFrameTime();
    }
    Rectangle getHitbox() {
        return {pos.x, pos.y, 48, 48};
    }
};

