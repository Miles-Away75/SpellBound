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
    FireballHeatSeeker
};

const std::unordered_map<std::string, std::vector<AttackType>> enemyAttackPatterns = {
    {"Enemy1", {FireballTowardsPlayer, MoveTowardsPlayer, GaurdSpread, RunFromPlayer}}
};

const float timeBetweenAttacks = 2.0f;

class Enemy {
    public:
        std::vector<AttackType> attackPaterns;
        int currentAttack = 0;
        float timeStartAttack = 0.0;
        bool doneAttack = false;
        Vector2 pos;
        Enemy(Vector2 n_pos, std::string name) : pos(n_pos) {
            attackPaterns = enemyAttackPatterns.at(name);
        }

        AttackType getAttack() {
            return attackPaterns[currentAttack];
        }
        void nextAttack() {
            currentAttack = (currentAttack + 1) % attackPaterns.size();
            timeStartAttack = GetTime();
        }
        void Update(Vector2 playerPos, std::vector<Spell>& activeSpells, SmartTexture& texture) {
 
            if (GetTime() - timeStartAttack > ((attackPaterns[currentAttack] == FireballHeatSeeker) ? timeBetweenAttacks * 2 : timeBetweenAttacks)) {
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
                        
                        pos.x += direction.x * 100 * GetFrameTime(); // Move speed of 100 pixels/second
                        pos.y += direction.y * 100 * GetFrameTime();
                        break;
                    
                    case RunFromPlayer: 
                        // Move away from the player's position
                        direction = Normalize({pos.x - playerPos.x, pos.y - playerPos.y});

                        pos.x += direction.x * 100 * GetFrameTime(); // Move speed of 100 pixels/second
                        pos.y += direction.y * 100 * GetFrameTime();
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
                    case FireballHeatSeeker:
                        direction = Normalize({playerPos.x - pos.x, playerPos.y - pos.y});
                        angle = atan2(direction.y, direction.x) * (180 / 3.14f);
                        activeSpells.push_back(Spell(Fireball, angle, pos, Opposing, FollowPlayer));
                        doneAttack = true;
                        break;
                    
                }
            }
            
            texture.draw(pos);
            
        }
};
