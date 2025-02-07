#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL3/SDL.h>

class Platform {
    public:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *screenTexture;

    public:
        Platform(const char*, int, int, int, int);
        void Update(const void*, int);
        void destroy();
        bool ProcessInput(uint8_t*);
};

#endif