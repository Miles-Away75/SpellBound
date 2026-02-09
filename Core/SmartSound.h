#include "raylib.h"


class SmartSound {
    public:
        ~SmartSound() {
            UnloadSound(s);
        }


        void Init(const char* path) {
            s = LoadSound(path);
        }
        void Play() {
            PlaySound(s);
        }
    private:
        Sound s;
};