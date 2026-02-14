#include "Game.h"


void Game::CollisionsGame() {
    // Spell Collisions with Enemy and Player
    CollisionsSpellEnemies();
    CollisionsSpellPlayers();
    CollisionsSpells();
    CollisionsPlayerPowerUps();
    if (health <= 0) {
        HandlePlayerDeath();
    }

}

void Game::CollisionsSpellPlayers() {
    // Spell Collisions with Player
    for (int i = 0; i < (int)activeSpells.size(); i++) {
        Spell spell = activeSpells[i];
        if (spell.mode == Opposing && spell.type != Gaurd && CheckCollisionRecs(spell.getHitbox(), {playerPos.x, playerPos.y, 42, 48})) {
            health -= spell.info.damage;
            timeHit = GetTime();
            // remove spell on hit
            activeSpells.erase(activeSpells.begin() + i);
            break;
        }
    }
}
void Game::CollisionsSpellEnemies() {
    // Spell Collisions with Enemies
    for (int i = 0; i < (int)activeSpells.size(); i++) {
        for (int j = 0; j < (int)enemies.size(); j++) {
            if (activeSpells[i].mode == Peaceful && activeSpells[i].type != Gaurd && CheckCollisionRecs(activeSpells[i].getHitbox(), {enemies[j].pos.x, enemies[j].pos.y, 42, 50})) {
                enemies[j].health -= activeSpells[i].info.damage * damageMultiplier;
                if (enemies[j].health <= 0) {
                    score += enemyScores.at(enemies[j].name);
                    enemies[j] = enemies.back();
                    enemies.pop_back();
                    PowerUpType powerUpType = GetRandomPowerUp();
                    if (powerUpType != None) {
                        powerUps.push_back(PowerUp(powerUpType, enemies[j].pos));
                    }
                }
                // Remove spell on hit
                activeSpells.erase(activeSpells.begin() + i);
                break;
            }
        }
    }
}
void Game::CollisionsSpells() {
    for (int i = 0; i < (int)activeSpells.size(); i++) {
        for (int j = 0; j < (int)activeSpells.size(); j++) {
            if (i == j) continue;
            if (activeSpells[i].mode != activeSpells[j].mode && // comes from different sides
                CheckCollisionRecs(activeSpells[i].getHitbox(), activeSpells[j].getHitbox()) && // colliding
                activeSpells[i].IsProtectingType() ^ activeSpells[j].IsProtectingType()) { // exactly one is a protecting type (gaurd or shield)
                // Remove both spells
                activeSpells.erase(activeSpells.begin() + std::max(i, j));
                activeSpells.erase(activeSpells.begin() + std::min(i, j));
                break;
            }
        }
    }
}
void Game::CollisionsPlayerPowerUps() {
    // Player with PowerUps
    for (int i = 0; i < (int)powerUps.size(); i++) {
        PowerUp powerUp = powerUps[i];
        if (CheckCollisionRecs(powerUp.getHitbox(), {playerPos.x, playerPos.y, 42, 48})) {
            powerUps.erase(powerUps.begin() + i);
            HandlePowerUpCollection(powerUp);
            break;
        }
    }
}