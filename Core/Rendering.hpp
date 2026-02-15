#pragma once


void DrawButton(Rectangle rect, const char* text, Color color = GREEN) {
    DrawRectangleRec(rect, color);
    int width = MeasureText(text, 20);
    int height = 20;
    DrawText(text, rect.x + (rect.width - width) / 2, rect.y + (rect.height - height) / 2, 20, BLACK);
}


