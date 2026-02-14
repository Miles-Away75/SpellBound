#include "Rendering.hpp"

Game::Game() {
    SetTargetFPS(60);
    
    InitWindow(ScreenWidth, ScreenHeight, "My Game");
    SetExitKey(KEY_NULL);
    SetWindowTitle("SpellBound");
    Image icon = LoadImage("Assets/Icon.png");
    SetWindowIcon(icon);
    UnloadImage(icon);



    loadAssets();

    loadLevel();
}
Game::~Game() {

    CloseWindow();
}
void Game::loadLevel() {
    activeSpells.clear();
    playerPos = {15, 15};
    playerVel = {0,0};
    for (auto & pair : spellTimes) {
        pair.second = -50.0f;
    }
    enemies.clear();
    for (auto pair : levels[level].enemyPositions) {
        enemies.push_back(Enemy(pair.second, pair.first));
    }
    health = 100;
    std::cout << "Loading Level\n";
}

void Game::loadAssets() {
    // Load textures, sounds, etc.
    spellSpritesheet.Init("Assets/Spells.png", 96, 96);
    playerSpritesheet.Init("Assets/Player.png", 126, 384);
    enemyTexture.Init("Assets/Enemies.png", 42, 50);
}
void Game::Run() {
    while (!WindowShouldClose() && isRunning) {
        Update();
    }
}
void Game::Update() {
    switch (state) {
        case MainMenu:
            UpdateMainMenu();
            return;
        case Playing:
            UpdateGame();
            return;
        case Controls:
            UpdateControls();
            return;
        case EndofLevel:
            UpdateEndofLevel();
            return;
        case GameOver:
            UpdateGameOver();
            return;

    }
}

