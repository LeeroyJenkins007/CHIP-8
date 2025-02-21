#ifndef MYGUI_H
#define MYGUI_H

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

#include <SDL3/SDL.h>

class MyGui {
    public:
        MyGui(SDL_Window* window, SDL_Renderer* renderer);
        void destroy();
};


#endif