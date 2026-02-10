#pragma once

#include "Enemy.h"
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

        void DrawCharacter();
        void DrawSpells();
        void DrawEnemies();
        void DrawControls();
        void DrawEndofLevel();

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
        std::unordered_map<int, SpellType> bindedSpells = {{KEY_J, Fireball}, {KEY_K, Gaurd}, {KEY_L, Shield}, {KEY_SEMICOLON, Thunder}};
        std::unordered_map<int, float> spellTimes = {{KEY_J, 0.0f}, {KEY_K, 0.0f}, {KEY_L, 0.0f}, {KEY_SEMICOLON, 0.0f}};
        std::vector<Spell> activeSpells;
        std::vector<SpellType> spellInventory = {};
        std::vector<Enemy> enemies;
        int health = 100;
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
            EndofLevel

        } state = MainMenu;

        std::vector<Level> levels = {
            {{{ "Enemy1", {400, 300}}}, Fireball},
            {{{"Boss1", {600, 600}}}, Thunder}
        };



};

#include "Game.hpp"
#include "MainMenu.hpp"
#include "GameState.hpp"
#include "Controls.hpp"
#include "Collisions.hpp"
#include "EndofLevel.hpp"



