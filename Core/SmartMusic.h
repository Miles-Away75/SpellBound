#include "raylib.h"


class SmartMusic {
    public:
        ~SmartMusic() {
            UnloadMusicStream(m);
        }


        void Init(const char* path, float volume) {
            m = LoadMusicStream(path);
            SetMusicVolume(m, volume);
        }
        void Update() {
            UpdateMusicStream(m);
        }
        void Play() {
            PlayMusicStream(m);
        }
    private:
        Music m;
};