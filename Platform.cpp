#include <SDL3/SDL.h>
#include <iostream>

#include "Platform.h"

Platform::Platform(const char* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight){
    if(!SDL_InitSubSystem(SDL_INIT_VIDEO)){
                SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
            }

            //create SDL3 window
            window = SDL_CreateWindow("CHIP-8 Emulator", windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
            if(!window){
                SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
            }else{
                std::cout << "Window Created\n";
            }

            //create SDL3 renderer
            renderer = SDL_CreateRenderer(window, NULL);
            if(!renderer){
                SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
            }else{
                std::cout << "Renderer Created\n";
            }

            //create SDL3 texture
            screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
            SDL_SetTextureScaleMode(screenTexture, SDL_SCALEMODE_NEAREST);
}

void Platform::Update(){
            //needs reworked
            uint8_t pixels[64 * 32]{};

            SDL_UpdateTexture(screenTexture, NULL, pixels, 32 * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, screenTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
}