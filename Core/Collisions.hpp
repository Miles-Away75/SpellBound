#include "Game.h"


void Game::CollisionsGame() {
    // Spell Collisions with Enemy and Player
    for (int i = 0; i < (int)activeSpells.size(); i++) {
        Spell spell = activeSpells[i];
        // Player
        if (spell.mode == Opposing && spell.type != Gaurd && CheckCollisionRecs(spell.getHitbox(), {playerPos.x, playerPos.y, 42, 48})) {
            health -= spell.info.damage;
            timeHit = GetTime();
            // remove spell on hit
            activeSpells.erase(activeSpells.begin() + i);
            break;
        }
        // Enemies
        for (int i = 0; i < (int)enemies.size(); i++) {
            Enemy enemy = enemies[i];
            if (spell.mode == Peaceful && spell.type != Gaurd && CheckCollisionRecs(spell.getHitbox(), {enemy.pos.x, enemy.pos.y, 42, 50})) {
                enemies[i].health -= spell.info.damage * damageMultiplier;
                if (enemies[i].health <= 0) {
                    score += enemyScores.at(enemy.name);
                    enemies[i] = enemies.back();
                    enemies.pop_back();
                    PowerUpType powerUpType = GetRandomPowerUp();
                    if (powerUpType != None) {
                        powerUps.push_back(PowerUp(powerUpType, enemy.pos));
                    }
                    
                }
                // Remove spell on hit
                activeSpells.erase(activeSpells.begin() + i);
                break;
            }
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
    // Player with PowerUps
    for (int i = 0; i < (int)powerUps.size(); i++) {
        PowerUp powerUp = powerUps[i];
        if (CheckCollisionRecs(powerUp.getHitbox(), {playerPos.x, playerPos.y, 42, 48})) {
            powerUps.erase(powerUps.begin() + i);
            if (powerUp.type == Health) {
                health += 20;
                if (health > maxHealth) health = maxHealth;
            }
            if (powerUp.type == Upgrade) {
                std::cout << "Upgrade Collected\n";
                state = Upgrading;
                GetRandomUpgrades();
                return;
            }
            if (powerUp.type == DamageUp) {
                damageMultiplier += 0.25f;
            }
            if (powerUp.type == SpeedUp) {
                playerAcceleration += 3.0 * std::pow(2, -timesIncreasedSpeed);
                timesIncreasedSpeed++;
            }
        }
    }
    if (health <= 0) {
        // Game Over logic here
        state = GameOver;
        maxHealth = 100;
        health = maxHealth;
        timeBetweenAttacks = 2.0f;
        activeSpells.clear();
        powerUps.clear();
        enemies.clear();
        playerPos = {15, 15};
        bindedSpells = {{KEY_J, Fireball}, {KEY_K, Gaurd}, {KEY_L, Shield}};
        spellTimes = {{KEY_J, -50.0f}, {KEY_K, -50.0f}, {KEY_L, -50.0f}};
        std::cout << "Game Over\n";
    }

}