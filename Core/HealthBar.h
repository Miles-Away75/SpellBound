#include "raylib.h"
#pragma once

class HealthBar {
    public:
        HealthBar(int maxHealth) : maxHealth(maxHealth), barHealth(maxHealth), realHealth(maxHealth) {}
        void Draw(Rectangle pos, int borderPx = 2) {
            DrawRectangleRec(pos, GRAY);
            DrawRectangleRec({pos.x, pos.y, pos.width * barHealth / maxHealth, pos.height}, RED);
            DrawRectangleLinesEx(pos, borderPx, BLACK); // Outline (2px thick)
        }
        void HandleHealthChange(int health) {
            realHealth = health;
        }
        void Update() {
            if (realHealth < barHealth) {
                velocity = -2.0;
            }
            else if (realHealth > barHealth) {
                velocity = 2.0;
            }
            else {
                velocity = 0.0f;
            }
            barHealth += velocity;
            if (barHealth < 0) barHealth = 0;
            if (barHealth > maxHealth) barHealth = maxHealth;

        }
        int maxHealth = 100;
        int barHealth = 100;
        int realHealth = 100;
        float velocity = 0.0f;
        
};