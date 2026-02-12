#include "Enemy.h"


void Enemy::Update(Vector2 playerPos, std::vector<Spell>& activeSpells, SmartTexture& texture) {
    std::cout << (float)health / enemyHealth.at(name) << "\n";
    Draw(texture);
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
                direction = {direction.x * enemySpeeds.at(name) * GetFrameTime(), direction.y * enemySpeeds.at(name) * GetFrameTime()};
                
                if (!CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, -1, (float)GetScreenWidth(), 1}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {-1, 0, 1, (float)GetScreenHeight()}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, (float)GetScreenHeight() - 1, (float)GetScreenWidth(), 1}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {(float)GetScreenWidth() - 1, 0, 1, (float)GetScreenHeight()})) {
                    pos.x += direction.x; 
                    pos.y += direction.y;
                }
                
                break;
            
            case RunFromPlayer: 
                // Move away from the player's position
                direction = Normalize({pos.x - playerPos.x, pos.y - playerPos.y});
                direction = {direction.x * enemySpeeds.at(name) * GetFrameTime(), direction.y * enemySpeeds.at(name) * GetFrameTime()};
                
                if (!CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, -1, (float)GetScreenWidth(), 1}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {-1, 0, 1, (float)GetScreenHeight()}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {0, (float)GetScreenHeight() - 1, (float)GetScreenWidth(), 1}) &&
                    !CheckCollisionRecs({pos.x + direction.x, pos.y + direction.y, 42, 50}, {(float)GetScreenWidth() - 1, 0, 1, (float)GetScreenHeight()})) {
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
            case HorizontalFireWall:
                for (int i = -GetScreenHeight()/50; i <= GetScreenHeight()/50; i++) {
                    activeSpells.push_back(Spell(Fireball, 0, {0.0f, i * 50.0f}, Opposing));
                }
                doneAttack = true;
                break;
            case VericalFireWall:
                for (int i = -GetScreenWidth()/50; i <= GetScreenWidth()/50; i++) {
                    activeSpells.push_back(Spell(Fireball, 90, {i * 50.0f, 0.0f}, Opposing));
                }
                doneAttack = true;
                break;
            
        }
    }
}