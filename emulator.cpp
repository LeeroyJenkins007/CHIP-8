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
//const char ROM[] = "../roms/test_opcode.ch8";
//const char ROM[] = "../roms/cavern.ch8";
//const char ROM[] = "../roms/delay_timer_test.ch8";


int main(){

    uint8_t target_fps = 60;

    uint32_t pixels[PXL_HEIGHT * PXL_WIDTH];

    Platform platform("CHIP-8 Emulator", PXL_WIDTH * 10, PXL_HEIGHT * 10, PXL_WIDTH, PXL_HEIGHT);


    myChip8.initialize();

    myChip8.loadGame(ROM);
    

    //string input;
    bool quit = false;
    //chrono::milliseconds frame_delta_t = chrono::milliseconds(0);
    auto t0 = chrono::steady_clock::now(); 
    int frame_time_ms = (1000 / target_fps);
    auto fps_t = t0; 
    auto fps_prev = fps_t;
    int fps_count = 0;
    while(!quit){
        //SDL_Event event;
        //runs through all events, doesn't get limited by frame rate
        quit = platform.ProcessInput(myChip8.keypad);

        myChip8.emulateCycle();

        auto t1 = chrono::steady_clock::now();
        auto frame_delta_t = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
        
        //cout << "Frame Time: " << frame_delta_t << "ms\n";

        if(frame_delta_t >= frame_time_ms){ 
            fps_count++;
            //cout << fps_count << "\n";
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
            t0 = chrono::steady_clock::now();
        }

        fps_t = chrono::steady_clock::now();
        auto seconds = chrono::duration_cast<chrono::seconds>(fps_t - fps_prev).count();
        if (seconds >= 1){
            cout<<"fps: " << fps_count << "\n";
            fps_count = 0;
            fps_prev = fps_t;
        }
        
        //slow down the cycles
        //this_thread::sleep_for(chrono::milliseconds(5));
    }


    platform.destroy();
    
    return 0;
}