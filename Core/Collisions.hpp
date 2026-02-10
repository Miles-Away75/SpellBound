#include "Game.h"


void Game::CollisionsGame() {
    // Spell Collisions with Enemy and Player
    for (Spell spell : activeSpells) {
        // Player
        if (spell.mode == Opposing && spell.type != Gaurd && CheckCollisionRecs(spell.getHitbox(), {playerPos.x, playerPos.y, 42, 48}) && GetTime() - timeHit > 1.0f) {
            health -= spell.info.damage;
            timeHit = GetTime();
        }
        // Enemies
        for (int i = 0; i < (int)enemies.size(); i++) {
            Enemy enemy = enemies[i];
            if (spell.mode == Peaceful && spell.type != Gaurd && CheckCollisionRecs(spell.getHitbox(), {enemy.pos.x, enemy.pos.y, 42, 50})) {
                enemies[i].health -= spell.info.damage;
                if (enemies[i].health <= 0) {
                    enemies[i] = enemies.back();
                    enemies.pop_back();
                }
                // Remove spell on hit
                spell = activeSpells.back();
                activeSpells.pop_back();
            }
        }
    }
    // Enemy with Player
    for (Enemy enemy : enemies) {
        if (CheckCollisionRecs({enemy.pos.x, enemy.pos.y, 42, 50}, {playerPos.x, playerPos.y, 42, 48}) && GetTime() - timeHit > 1.0f) {
            health -= 10;
            timeHit = GetTime();
        }
    }
    // Spells with Spells (specifically gaurds v others)
    for (int i = 0; i < (int)activeSpells.size(); i++) {

        Spell spell1 = activeSpells[i];

        for (int j = 0; j < (int)activeSpells.size(); j++) {

            if (i == j) continue;
            Spell spell2 = activeSpells[j];
            if (spell1.mode != spell2.mode && // comes from different sides
                CheckCollisionRecs(spell1.getHitbox(), spell2.getHitbox()) && // colliding
                spell1.IsProtectingType() ^ spell2.IsProtectingType()) { // exactly one is a protecting type (gaurd or shield)
                // Remove both spells
                activeSpells.erase(activeSpells.begin() + std::max(i, j));
                activeSpells.erase(activeSpells.begin() + std::min(i, j));
                
                break;
            }
        }
    }
    if (health <= 0) {
        // Game Over logic here
        state = MainMenu;
        health = 100;
    }

}