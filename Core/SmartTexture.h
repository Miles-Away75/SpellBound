#include "raylib.h"



class SmartTexture {
    public:
        ~SmartTexture() {
            UnloadTexture(t);
        }


        void Init(const char* path, int w, int h) {
            Image i = LoadImage(path);
            ImageResize(&i, w ,h);
            t = LoadTextureFromImage(i);
            UnloadImage(i);
        }
        float width() {
            return t.width;
        }
        float height() {
            return t.height;
        }
        void draw(Vector2 pos, float scale = 1.0f) {
            DrawTextureEx(t, pos, 0.0f, scale, WHITE);
        }
        void drawWarped(Rectangle destPos) {
            DrawTexturePro(t, {0,0, (float)t.width, (float)t.height}, destPos, {0,0}, 0.0f, WHITE);
        }
    private:
        Texture t;
};

class Spritesheet {
    public:
        ~Spritesheet() {
            UnloadTexture(t);
        }


        void Init(const char* path, int w, int h) {
            Image i = LoadImage(path);
            ImageResize(&i, w ,h);
            t = LoadTextureFromImage(i);
            UnloadImage(i);
        }
        float width() {
            return t.width;
        }
        float height() {
            return t.height;
        }
        void draw(Rectangle spritePos, Rectangle destPos, float angle=0.0f) {
            Vector2 origin = {destPos.width/2, destPos.height/2};
            DrawTexturePro(t, spritePos, destPos, origin, angle, WHITE);
        }
        
    private:
        Texture t;
};