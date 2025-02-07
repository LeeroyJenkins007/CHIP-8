#include <iostream>
#include <chrono>
#include <thread>
//#include <SDL3/SDL.h>

#include "Chip8.h"
#include "Platform.h"

using namespace std;

Chip8 myChip8;

//const char ROM[] = "../roms/chip8-logo.ch8";
//const char ROM[] = "../roms/2-ibm-logo.ch8";
//const char  ROM[] = "../roms/3-corax+.ch8";
//const char  ROM[] = "../roms/4-flags.ch8";
//const char  ROM[] = "../roms/5-quirks.ch8";
const char  ROM[] = "../roms/6-keypad.ch8";
//const char  ROM[] = "../roms/7-beep.ch8";
//const char  ROM[] = "../roms/8-scrolling.ch8";


int main(){

    uint32_t pixels[PXL_HEIGHT * PXL_WIDTH];

    Platform platform("CHIP-8 Emulator", PXL_WIDTH * 10, PXL_HEIGHT * 10, PXL_WIDTH, PXL_HEIGHT);


    myChip8.initialize();

    myChip8.loadGame(ROM);
    

    //string input;
    bool quit = false;
    while(!quit){
        //SDL_Event event;
        //runs through all events, doesn't get limited by frame rate
        quit = platform.ProcessInput(myChip8.keypad);
        
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
            platform.Update(pixels, PXL_WIDTH * sizeof(uint32_t));
        }
        //slow down the cycles
        this_thread::sleep_for(chrono::milliseconds(10));
    }


    platform.destroy();
    
    return 0;
}