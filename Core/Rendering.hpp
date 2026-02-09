#pragma once


void DrawButton(Rectangle rect, const char* text) {
    DrawRectangleRec(rect, GREEN);
    int width = MeasureText(text, 20);
    int height = 20;
    DrawText(text, rect.x + (rect.width - width) / 2, rect.y + (rect.height - height) / 2, 20, BLACK);
}


