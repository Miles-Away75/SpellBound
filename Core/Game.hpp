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

    enemies.push_back(Enemy({500, 500}, "Enemy1"));

}
Game::~Game() {

    CloseWindow();
}


void Game::loadAssets() {
    // Load textures, sounds, etc.
    spellSpritesheet.Init("Assets/Spells.png", 96, 96);
    playerSpritesheet.Init("Assets/Player.png", 126, 384);
    enemyTexture.Init("Assets/Enemies.png", 42, 50);
    powerUpSpritesheet.Init("Assets/Powerups.png", 96, 84);
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
        case Upgrading:
            UpdateUpgrading();
            return;
        case GameOver:
            UpdateGameOver();
            return;

    }
}

