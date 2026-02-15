#pragma once

#include "Enemy.h"
#include "Abilities.h"
#include "SmartMusic.h"
#include "SmartSound.h"
#include "Rendering.hpp"
#include "PowerUp.h"
#include "HealthBar.h"

#include <vector>
#include <iostream>

const int ScreenWidth = 800;
const int ScreenHeight = 600;

const int playerFPS = 8;

float playerAcceleration = 0.5;

float damageMultiplier = 1.0f;

int maxHealth = 100;

enum UpgradeType {
    SpellUpgrade,
    AbilityUpgrade,
    UpMaxHealth,
    UPGRADE_COUNT
};
const std::unordered_map<UpgradeType, int> upgradePrices = {
    {SpellUpgrade, 30},
    {AbilityUpgrade, 20},
    {UpMaxHealth, 10}
};

class Game {
    public:
        Game();
        ~Game();

        void loadAssets();
        
        void Run();

        void Update();
        void UpdateMainMenu();
        void UpdateGame();
        void UpdateUpgrading();
        void UpdateGameOver();

        void DrawCharacter();
        void DrawSpells();
        void DrawEnemies();
        void DrawUpgrading();
        void DrawPowerUps();

        void DrawGameOver();

        void EventsGame();
        void GetPlayerControls();
        void EventsUpgrading();

        void CollisionsGame();
        void CollisionsSpellPlayers();
        void CollisionsSpellEnemies();
        void CollisionsSpells();
        void CollisionsPlayerPowerUps();

        bool ShouldSpawnEnemy();
        PowerUpType GetRandomPowerUp();

        void GetRandomUpgrades();
        void HandlePlayerAnimation();
        void HandlePlayerDeath();
        void GetPlayerSpellControls();
        void GetPlayerAbilityControls();
        void HandlePowerUpCollection(PowerUp& powerUp);
        
    private:
        Spritesheet spellSpritesheet;
        Spritesheet playerSpritesheet;
        Spritesheet powerUpSpritesheet;
        Spritesheet enemySpritesheet;

        bool isRunning = true;

        Vector2 playerPos = {0,0};
        Vector2 playerVel = {0,0};
        std::unordered_map<int, SpellType> bindedSpells = {{KEY_J, Fireball}, {KEY_K, Gaurd}, {KEY_L, Shield}};
        std::unordered_map<int, AbilityType> bindedAbilities = {{KEY_R, Teleport}, {KEY_F, Dash}};
        std::unordered_map<int, float> spellTimes = {{KEY_J, -50.0f}, {KEY_K, -50.0f}, {KEY_L, -50.0f}};
        std::unordered_map<int, float> abilityTimes = {{KEY_R, -50.0f}, {KEY_F, -50.0f}};
        std::vector<Spell> activeSpells;
        std::vector<Enemy> enemies;
        std::vector<PowerUp> powerUps;
        std::vector<UpgradeType> currentUpgrades = {};
        int health = maxHealth;
        HealthBar playerHealthBar = HealthBar(maxHealth);
        int coins = 0;
        int timesIncreasedSpeed = 0;
        float timeHit = 0.0f;

        float timeSinceLastSpawn = 0.0f;
        float timeBetweenSpawns = 5.0f;


        std::unordered_map<float, std::vector<Rectangle>> playerSprites = { // angle : sprite (0 == RIGHT, 90 == DOWN, 180 == LEFT, 270 == UP)
            {90, {{0, 0, 42, 48}, {42, 0, 42, 48}, {84, 0, 42, 48}}},
            {135, {{0, 48, 42, 48}, {42, 48, 42, 48}, {84, 48, 42, 48}}},
            {180, {{0, 96, 42, 48}, {42, 96, 42, 48}, {84, 96, 42, 48}}},
            {225, {{0, 144, 42, 48}, {42, 144, 42, 48}, {84, 144, 42, 48}}},
            {270, {{0, 192, 42, 48}, {42, 192, 42, 48}, {84, 192, 42, 48}}},
            {315, {{0, 240, 42, 48}, {42, 240, 42, 48}, {84, 240, 42, 48}}},
            {0, {{0, 288, 42, 48}, {42, 288, 42, 48}, {84, 288, 42, 48}}},
            {45, {{0, 336, 42, 48}, {42, 336, 42, 48}, {84, 336, 42, 48}}}
        };
        float playerDirection = 90;
        int playerAnimFrame = 0;
        float timeSinceFrameStart = 0.0f;
        
        enum GameState {
            MainMenu,
            Playing,
            Upgrading,
            GameOver

        } state = MainMenu;




};

#include "Game.hpp"
#include "GameEvents.hpp"
#include "GameState.hpp"
#include "GameRendering.hpp"
#include "MainMenu.hpp"
#include "Upgrading.hpp"
#include "Collisions.hpp"
#include "GameOver.hpp"


