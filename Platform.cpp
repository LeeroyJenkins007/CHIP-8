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

void Platform::Update(const void* pixels, int pitch){

            SDL_UpdateTexture(screenTexture, NULL, pixels, pitch);
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, screenTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
}

bool Platform::ProcessInput(uint8_t* keypad){
    bool quit = false;

    SDL_Event event;

    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_EVENT_QUIT:
                quit = true;
                break;    
            case SDL_EVENT_KEY_DOWN:
                std::cout << "Key Press Down\n";
                switch(event.key.key){
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_X:
                        keypad[0x0] = 1;
                        break;
                    case SDLK_1:
                        keypad[0x1] = 1;
                        break;
                    case SDLK_2:
                        keypad[0x2] = 1;
                        break;
                    case SDLK_3:
                        keypad[0x3] = 1;
                        break;
                    case SDLK_Q:
                        keypad[0x4] = 1;
                        break;
                    case SDLK_W:
                        keypad[0x5] = 1;
                        break;
                    case SDLK_E:
                        keypad[0x6] = 1;
                        break;
                    case SDLK_A:
                        keypad[0x7] = 1;
                        break;
                    case SDLK_S:
                        keypad[0x8] = 1;
                        break;
                    case SDLK_D:
                        keypad[0x9] = 1;
                        break;
                    case SDLK_Z:
                        keypad[0xA] = 1;
                        break;
                    case SDLK_C:
                        keypad[0xB] = 1;
                        break;
                    case SDLK_4:
                        keypad[0xC] = 1;
                        break;
                    case SDLK_R:
                        keypad[0xD] = 1;
                        break;
                    case SDLK_F:
                        keypad[0xE] = 1;
                        break;
                    case SDLK_V:
                        keypad[0xF] = 1;
                        break;
                    default:
                        //std::cout << "Unknown Key Down\n";
                        break;
                }
                break;
            case SDL_EVENT_KEY_UP:
                std::cout << "Key Press UP\n";
                switch(event.key.key){
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_X:
                        keypad[0x0] = 0;
                        break;
                    case SDLK_1:
                        keypad[0x1] = 0;
                        break;
                    case SDLK_2:
                        keypad[0x2] = 0;
                        break;
                    case SDLK_3:
                        keypad[0x3] = 0;
                        break;
                    case SDLK_Q:
                        keypad[0x4] = 0;
                        break;
                    case SDLK_W:
                        keypad[0x5] = 0;
                        break;
                    case SDLK_E:
                        keypad[0x6] = 0;
                        break;
                    case SDLK_A:
                        keypad[0x7] = 0;
                        break;
                    case SDLK_S:
                        keypad[0x8] = 0;
                        break;
                    case SDLK_D:
                        keypad[0x9] = 0;
                        break;
                    case SDLK_Z:
                        keypad[0xA] = 0;
                        break;
                    case SDLK_C:
                        keypad[0xB] = 0;
                        break;
                    case SDLK_4:
                        keypad[0xC] = 0;
                        break;
                    case SDLK_R:
                        keypad[0xD] = 0;
                        break;
                    case SDLK_F:
                        keypad[0xE] = 0;
                        break;
                    case SDLK_V:
                        keypad[0xF] = 0;
                        break;
                    default:
                        //std::cout << "Unknown Key Up\n";
                        break;
                }
                break;
            default: //event type
                //std::cout << "unknown event type\n";
                break;
        }//Switch EVENT TYPE
    } //while Poll events
    return quit;
}

void Platform::destroy(){
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}