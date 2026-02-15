#include "Game.h"
#include "Math.h"

std::string GetRandomEnemy() {
    int r = GetRandomValue(0, 100);
    //if (r < 80) return "Enemy1";
    //return "Boss1";
    return "Enemy1";
}

void Game::GetRandomUpgrades() {
    currentUpgrades.clear();
    for (int i = 0; i < 3; i++) {
        currentUpgrades.push_back((UpgradeType)random(0, UpgradeType::UPGRADE_COUNT));
    }
}
bool Game::ShouldSpawnEnemy() {
    if (GetTime() - timeSinceLastSpawn > timeBetweenSpawns && GetRandomValue(0, 100) < 25 ) {
        timeSinceLastSpawn = GetTime();
        return true;  
    }
    return false;
}
PowerUpType Game::GetRandomPowerUp() {
    int r = GetRandomValue(0, 100);
    if (r < 40) return Health;

    if (r < 50) return DamageUp;

    if (r < 60) return SpeedUp;

    if (r < 70) return Upgrade;

    return None;
}
void Game::HandlePlayerDeath() {
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
void Game::UpdateGame() {
    
    EventsGame();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCharacter();
        DrawPowerUps();
        DrawEnemies();
        DrawSpells();
        DrawEffectIcons();
    EndDrawing();

    CollisionsGame();
    if (state != Playing) return;
    HandlePlayerAnimation();
    HandleEffects();
}


void Game::HandlePlayerAnimation() {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
        
        timeSinceFrameStart += GetFrameTime();
        if (timeSinceFrameStart > 1.0f / playerFPS) {
            playerAnimFrame = (playerAnimFrame + 1) % playerSprites[playerDirection].size();
            timeSinceFrameStart = 0.0f;
        }
    } 
    else {
        playerAnimFrame = 0;
    }
}
void Game::HandlePowerUpCollection(PowerUp& powerUp) {
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
            hasDamageUp = true;
            startOfDamageUp = GetTime();
        }
        if (powerUp.type == SpeedUp) {
            hasSpeedUp = true;
            startOfSpeedUp = GetTime();
        }
}
void Game::HandleEffects() {
    if (hasDamageUp && GetTime() - startOfDamageUp > 10.0f) {
        hasDamageUp = false;
    }
    if (hasSpeedUp && GetTime() - startOfSpeedUp > 10.0f) {
        hasSpeedUp = false;
    }
}
