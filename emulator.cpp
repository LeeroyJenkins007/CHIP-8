#include <iostream>
#include <SDL3/SDL.h>

#include "Chip8.h"

using namespace std;

Chip8 myChip8;

const char ROM[] = "./roms/IBM Logo.ch8";

int main(){

    if(!SDL_InitSubSystem(SDL_INIT_VIDEO)){
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    }

    // sizing using 'logical sizes' so it's not actual pixle size
    auto window = SDL_CreateWindow("CHIP-8", PXL_WIDTH * 10, PXL_HEIGHT * 10, SDL_WINDOW_RESIZABLE);
    if(!window){
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    }

    myChip8.initialize();
    //myChip8.printMe();

    myChip8.loadGame(ROM);
    //myChip8.printMem(0x50, 650);
    myChip8.emulateCycle();


    bool isRunning = true;
    while(isRunning){
        SDL_Event event;
        SDL_PollEvent(&event);

        //Rendering code
        
    }


    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    //myChip8.Grant();
    return 0;
}