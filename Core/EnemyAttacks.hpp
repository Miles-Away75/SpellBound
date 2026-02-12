#include "Enemy.h"

const float wallSpacing = 75;

void Enemy::Update(Vector2 playerPos, std::vector<Spell>& activeSpells, SmartTexture& texture) {
    std::cout << (float)health / enemyHealth.at(name) << "\n";
    Draw(texture);
    if (GetTime() - timeStartAttack >  timeBetweenAttacks) {
        nextAttack();
        doneAttack = false;
        if (getAttack() == GoToRandomPosition) {
            destination = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
        }
    }
    Vector2 direction;
    Rectangle recX;
    Rectangle recY;
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
       
                recX = {pos.x + direction.x, pos.y, 42, 50};
                recY = {pos.x, pos.y + direction.y, 42, 50};
                if (RectInLevel(recX)) {
                    pos.x += direction.x; 
                }
                if (RectInLevel(recY)) {
                    pos.y += direction.y;
                }      
                break;
            
            case RunFromPlayer: 
                // Move away from the player's position
                direction = Normalize({pos.x - playerPos.x, pos.y - playerPos.y});
                direction = {direction.x * enemySpeeds.at(name) * GetFrameTime(), direction.y * enemySpeeds.at(name) * GetFrameTime()};
                
                recX = {pos.x + direction.x, pos.y, 42, 50};
                recY = {pos.x, pos.y + direction.y, 42, 50};
                if (RectInLevel(recX)) {
                    pos.x += direction.x; 
                }
                if (RectInLevel(recY)) {
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
                for (int i = -GetScreenHeight()/wallSpacing; i <= GetScreenHeight()/wallSpacing; i++) {
                    activeSpells.push_back(Spell(Fireball, 0, {0.0f, i * wallSpacing}, Opposing));
                }
                doneAttack = true;
                break;
            case VericalFireWall:
                for (int i = -GetScreenWidth()/wallSpacing; i <= GetScreenWidth()/wallSpacing; i++) {
                    activeSpells.push_back(Spell(Fireball, 90, {i * wallSpacing, 0.0f}, Opposing));
                }
                doneAttack = true;
                break;
            case GoToRandomPosition:
                direction = Normalize({destination.x - pos.x, destination.y - pos.y});
                direction = {direction.x * enemySpeeds.at(name) * GetFrameTime(), direction.y * enemySpeeds.at(name) * GetFrameTime()};
                recX = {pos.x + direction.x, pos.y, 42, 50};
                recY = {pos.x, pos.y + direction.y, 42, 50};
                if (RectInLevel(recX)) {
                    pos.x += direction.x; 
                }
                if (RectInLevel(recY)) {
                    pos.y += direction.y;
                }
                if (pos.x == destination.x && pos.y == destination.y) {
                    destination = {random(0, GetScreenWidth()), random(0, GetScreenHeight())};
                }
                break;
            
        }
    }
}