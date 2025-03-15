#ifndef MYGUI_H
#define MYGUI_H

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "imgui_memory_editor.h"

#include "Platform.h"

#include <SDL3/SDL.h>

struct GraphicalInterface {
    int windowWidth;
    int windowHeight;
    int emuWidth;
    int emuHeight;
    int pxlWidth;
    int pxlHeight;
    const char* windowName;
};

class MyGui {
    private:
        ImTextureID textureID;
    public:
        Platform platform;
        GraphicalInterface graphicsData;
        //static ImGuiIO& io;
    public:
        MyGui(GraphicalInterface*);
        void destroy();
        bool ProcessEvent(uint8_t*);
        void Update(const void*, int);
};


#endif