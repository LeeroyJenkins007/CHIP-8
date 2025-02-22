#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL3/SDL.h>

class Platform {
    public:
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Texture *screenTexture = nullptr;

    public:
        Platform();
        Platform(const char*, int, int, int, int);
        void Render(const void*, int);
        void destroy();
        bool ProcessInput(uint8_t*, SDL_Event);
};

#endif