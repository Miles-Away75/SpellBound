#include <cmath>
#pragma once
#include "raylib.h"

Vector2 Normalize(Vector2 v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0) {
        v.x /= length;
        v.y /= length;
    }
    return v;
}