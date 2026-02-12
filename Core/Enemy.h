#include "raylib.h"
#include "Spells.h"
#include <vector>
#include <cmath>
#include <iostream>
#pragma once



enum AttackType {
    FireSpread,
    GaurdSpread,
    MoveTowardsPlayer,
    RunFromPlayer,
    FireballTowardsPlayer,
    GaurdTowardsPlayer,
    ThunderTowardsPlayer,
    HorizontalFireWall,
    VericalFireWall
};

const std::unordered_map<std::string, std::vector<AttackType>> enemyAttackPatterns = {
    {"Enemy1", {FireballTowardsPlayer, MoveTowardsPlayer, ThunderTowardsPlayer, GaurdSpread, RunFromPlayer}},
    {"Boss1", {FireballTowardsPlayer, MoveTowardsPlayer, FireSpread, GaurdSpread, HorizontalFireWall, VericalFireWall, RunFromPlayer, ThunderTowardsPlayer}}
};
const std::unordered_map<std::string, int> enemyHealth = {
    {"Enemy1", 30},
    {"Boss1", 100}
};
const std::unordered_map<std::string, float> enemySpeeds = {
    {"Enemy1", 100},
    {"Boss1", 150}
};

const float timeBetweenAttacks = 2.0f;

class Enemy {
    public:
        std::vector<AttackType> attackPaterns;
        int currentAttack = 0;
        float timeStartAttack = 0.0;
        bool doneAttack = false;
        Vector2 pos;
        int health;
        std::string name;
        Enemy(Vector2 n_pos, std::string n_name) : pos(n_pos), name(n_name) {
            attackPaterns = enemyAttackPatterns.at(name);
            health = enemyHealth.at(name);
        }

        AttackType getAttack() {
            return attackPaterns[currentAttack];
        }
        void nextAttack() {
            currentAttack = (currentAttack + 1) % attackPaterns.size();
            timeStartAttack = GetTime();
        }
        void Draw(SmartTexture& texture) {
            texture.draw(pos);
            // draw health bar
            DrawRectangleRec({pos.x, pos.y - 10, 48, 5}, GRAY);
            DrawRectangleRec({pos.x, pos.y - 10, 48.0f * (health / enemyHealth.at(name)), 5}, RED);
        }
        void Update(Vector2 playerPos, std::vector<Spell>& activeSpells, SmartTexture& texture);
};

#include "EnemyAttacks.hpp"