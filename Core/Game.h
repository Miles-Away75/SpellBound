#pragma once

#include "Enemy.h"
#include "Abilities.h"
#include "SmartMusic.h"
#include "SmartSound.h"
#include "Rendering.hpp"

#include <vector>
#include <iostream>

const int ScreenWidth = 800;
const int ScreenHeight = 600;

struct Level {
    std::unordered_map<std::string, Vector2> enemyPositions;
    SpellType reward;
};

class Game {
    public:
        Game();
        ~Game();

        void loadAssets();
        void loadLevel();
        
        void Run();

        void Update();
        void UpdateMainMenu();
        void UpdateGame();
        void UpdateControls();
        void UpdateEndofLevel();
        void UpdateGameOver();

        void DrawCharacter();
        void DrawSpells();
        void DrawEnemies();
        void DrawControls();
        void DrawEndofLevel();
        void DrawGameOver();

        void EventsGame();
        void GetPlayerControls();
        void EventsControls();
        void EventsEndofLevel();

        void CollisionsGame();
        
    private:
        Spritesheet spellSpritesheet;
        Spritesheet playerSpritesheet;
        SmartTexture enemyTexture;

        bool isRunning = true;
        int level = 0;

        Vector2 playerPos = {0,0};
        Vector2 playerVel = {0,0};
        std::unordered_map<int, SpellType> bindedSpells = {{KEY_J, Fireball}, {KEY_K, Gaurd}, {KEY_L, Shield}};
        std::unordered_map<int, AbilityType> bindedAbilities = {{KEY_R, Teleport}, {KEY_F, Dash}};
        std::unordered_map<int, float> spellTimes = {{KEY_J, -50.0f}, {KEY_K, -50.0f}, {KEY_L, -50.0f}};
        std::unordered_map<int, float> abilityTimes = {{KEY_R, -50.0f}, {KEY_F, -50.0f}};
        std::vector<Spell> activeSpells;
        std::vector<SpellType> spellInventory = {};
        std::vector<AbilityType> abilityInventory = {};
        std::vector<Enemy> enemies;
        int health = 50;
        float timeHit = 0.0f;


        std::unordered_map<float, Rectangle> playerSprites = { // angle : sprite (0 == RIGHT, 90 == DOWN, 180 == LEFT, 270 == UP)
            {90, {0, 0, 42, 48}},
            {135, {42, 0, 42, 48}},
            {180, {84, 0, 42, 48}},
            {225, {0, 48, 42, 48}},
            {270, {42, 48, 42, 48}},
            {315, {84, 48, 42, 48}},
            {0, {0, 96, 42, 48}},
            {45, {42, 96, 42, 48}}
        };
        float playerDirection = 90;
        
        enum GameState {
            MainMenu,
            Playing,
            Controls,
            EndofLevel,
            GameOver

        } state = MainMenu;

        std::vector<Level> levels = {
            {{{ "Enemy1", {400, 300}}}, Fireball},
            {{{"Boss1", {600, 400}}}, Thunder}
        };



};

#include "Game.hpp"
#include "MainMenu.hpp"
#include "GameState.hpp"
#include "Controls.hpp"
#include "Collisions.hpp"
#include "EndofLevel.hpp"
#include "GameOver.hpp"


