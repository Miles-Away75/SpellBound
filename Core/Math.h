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
    Rectangle levelBounds = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    // check all 4 corners of the rectangle
    return CheckCollisionPointRec({rect.x, rect.y}, levelBounds) &&
           CheckCollisionPointRec({rect.x + rect.width, rect.y}, levelBounds) &&
           CheckCollisionPointRec({rect.x, rect.y + rect.height}, levelBounds) &&
           CheckCollisionPointRec({rect.x + rect.width, rect.y + rect.height}, levelBounds);
}
float random(float a, float b) {
    return GetRandomValue(a * 1000, b * 1000) / 1000;
} 
template <typename T>
bool contains(std::vector<T> vec, T element) {
    for (T el : vec) {
        if (el == element) return true;
    }
    return false;
}