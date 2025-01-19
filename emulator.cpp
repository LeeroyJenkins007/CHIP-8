#include <iostream>
#include <direct.h>
#include <chrono>
#include <thread>
#include <SDL3/SDL.h>

#include "Chip8.h"

using namespace std;

Chip8 myChip8;

const char ROM[] = "../roms/2-ibm-logo.ch8";
//const char ROM[] = "../roms/chip8-logo.ch8";

int main(){

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *screenTexture = NULL;
    SDL_Surface *bitmapSurface = NULL;

    uint32_t pixels[PXL_HEIGHT * PXL_WIDTH];


    if(!SDL_InitSubSystem(SDL_INIT_VIDEO)){
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
    }

    // sizing using 'logical sizes' so it's not actual pixle size
    //window = SDL_CreateWindow("CHIP-8", PXL_WIDTH * 20, PXL_HEIGHT * 20, SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("CHIP-8 Emulator", PXL_WIDTH * 10, PXL_HEIGHT * 10, SDL_WINDOW_RESIZABLE);
    if(!window){
        SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
    }else{
        cout << "Window Created\n";
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
    }else{
        cout << "Renderer Created\n";
    }

    //SDL_SetRenderLogicalPresentation(renderer, PXL_WIDTH, PXL_HEIGHT, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
    //SDL_RendererLogicalPresentation(SDL_LOGICAL_PRESENTATION_DISABLED);

    /*
    //char buffer[1024];
    //cout << "CWD: " << getcwd(buffer, 1024) << "\n";
    bitmapSurface = SDL_LoadBMP("../testData/snail.bmp");
    if(bitmapSurface == NULL){
        cout << "Failed to find Surface: " << SDL_GetError() << "\n";
    }

    bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    if(bitmapTex == NULL){
        cout << "Failed to create texture: " << SDL_GetError() << "\n";
    }
    SDL_DestroySurface(bitmapSurface);
    */

    //create texture
    screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, PXL_WIDTH, PXL_HEIGHT);


    myChip8.initialize();
    //myChip8.printMe();

    myChip8.loadGame(ROM);
    //myChip8.printMem(0x50, 650);
    

    //string input;
    bool isRunning = true;
    while(isRunning){
        SDL_Event event;
        //runs through all events, doesn't get limited by frame rate
        while (SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                isRunning = false;
            }
        }
        
        myChip8.emulateCycle();
        
        if(myChip8.drawFlag){
            myChip8.drawFlag = false;
            //write gfx data to pixel buffer
            uint8_t pixel;
            for(int i = 0; i < PXL_HEIGHT * PXL_WIDTH; i++){
                pixel = myChip8.gfx[i];
                //format is ARGB
                pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
            }
            //Rendering code
            SDL_UpdateTexture(screenTexture, NULL, pixels, PXL_WIDTH * sizeof(uint32_t));
            SDL_RenderClear(renderer);
            SDL_RenderTexture(renderer, screenTexture, NULL, NULL);
            SDL_RenderPresent(renderer);
        }
        //cin >> input;
        //slow down the cycles
        this_thread::sleep_for(chrono::milliseconds(100));
    }


    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    //myChip8.Grant();
    return 0;
}