#include "raylib.h"
#include "Spells.h"
#include <vector>
#include <cmath>
#include <iostream>



enum AttackType {
    FireSpread,
    GaurdSpread,
    MoveTowardsPlayer,
    RunFromPlayer,
    FireballTowardsPlayer,
    GaurdTowardsPlayer,
    ThunderTowardsPlayer
};

const std::unordered_map<std::string, std::vector<AttackType>> enemyAttackPatterns = {
    {"Enemy1", {FireballTowardsPlayer, MoveTowardsPlayer, ThunderTowardsPlayer, GaurdSpread, RunFromPlayer}},
    {"Boss1", {FireballTowardsPlayer, MoveTowardsPlayer, FireSpread, GaurdSpread, RunFromPlayer, ThunderTowardsPlayer}}
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
        void Update(Vector2 playerPos, std::vector<Spell>& activeSpells, SmartTexture& texture) {
 
            if (GetTime() - timeStartAttack >  timeBetweenAttacks) {
                nextAttack();
                doneAttack = false;
            }
            Vector2 direction;
            float angle;
            if (!doneAttack) {
                switch (getAttack()) {
                    case FireSpread: 
                        for (float dir : {0, 45, 90, 135, 180, 225, 270, 315}) {
                            activeSpells.push_back(Spell(Fireball, dir, pos, Opposing)); 
                        }
                        std::cout << "Enemy Attacking with Fire Spread!" << std::endl;
                        doneAttack = true;
                        break;
                    
                    case GaurdSpread: 
                        for (float dir : {0, 45, 90, 135, 180, 225, 270, 315}) {
                            activeSpells.push_back(Spell(Gaurd, dir, pos, Opposing));
                        }
                        doneAttack = true;
                        break;
                    
                    case MoveTowardsPlayer: 
                        // Move towards the player's position
                        direction = Normalize({playerPos.x - pos.x, playerPos.y - pos.y});

                        direction = {direction.x * enemySpeeds.at("Enemy1") * GetFrameTime(), direction.y * enemySpeeds.at("Enemy1") * GetFrameTime()};
                        
                        if (CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()})) {
                            pos.x += direction.x; 
                            pos.y += direction.y;
                        }
                        
                        break;
                    
                    case RunFromPlayer: 
                        // Move away from the player's position
                        direction = Normalize({pos.x - playerPos.x, pos.y - playerPos.y});

                        direction = {direction.x * enemySpeeds.at("Enemy1") * GetFrameTime(), direction.y * enemySpeeds.at("Enemy1") * GetFrameTime()};
                        
                        if (CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()})) {
                            pos.x += direction.x; 
                            pos.y += direction.y;
                        }
                        break;
                    case FireballTowardsPlayer:
                        direction = Normalize({playerPos.x - pos.x, playerPos.y - pos.y});
                        angle = atan2(direction.y, direction.x) * (180 / 3.14f);
                        activeSpells.push_back(Spell(Fireball, angle, pos, Opposing));
                        doneAttack = true;
                        break;
                    case GaurdTowardsPlayer:
                        direction = Normalize({playerPos.x - pos.x, playerPos.y - pos.y});
                        angle = atan2(direction.y, direction.x) * (180 / 3.14f);
                        activeSpells.push_back(Spell(Gaurd, angle, pos, Opposing));
                        doneAttack = true;
                        break;
                    case ThunderTowardsPlayer:
                        direction = Normalize({playerPos.x - pos.x, playerPos.y - pos.y});
                        angle = atan2(direction.y, direction.x) * (180 / 3.14f);
                        activeSpells.push_back(Spell(Thunder, angle, pos, Opposing));
                        doneAttack = true;
                        break;
                    
                }
            }
            
            texture.draw(pos);
            // draw health bar
            DrawRectangleRec({pos.x, pos.y - 10, 48, 5}, GRAY);
            DrawRectangleRec({pos.x, pos.y - 10, 48.0f * (health / enemyHealth.at(name)), 5}, RED);
            //std::cout << health/enemyHealth.at("Enemy1") << std::endl;
            std::cout << health << std::endl;
            
        }
};
