#include <cmath>
#pragma once
#include "raylib.h"
#include <random>
#include <chrono>

Vector2 Normalize(Vector2 v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0) {
        v.x /= length;
        v.y /= length;
    }
    return v;
}
float Distance(Vector2 a, Vector2 b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}
bool RectInLevel(Rectangle rect) {
    if (!CheckCollisionRecs(rect, {0, -1, (float)GetScreenWidth(), 1}) &&
        !CheckCollisionRecs(rect, {-1, 0, 1, (float)GetScreenHeight()}) &&
        !CheckCollisionRecs(rect, {0, (float)GetScreenHeight() - 1, (float)GetScreenWidth(), 1}) &&
        !CheckCollisionRecs(rect, {(float)GetScreenWidth() - 1, 0, 1, (float)GetScreenHeight()})) {
        return true;
    }
    return false;
}
float random(float a, float b) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 


    std::uniform_int_distribution<> distrib(1, 100); 

    // 3. Generate the random number
    int random_num = distrib(gen);
    return a + (b - a) * random_num / 100.0f;
} 