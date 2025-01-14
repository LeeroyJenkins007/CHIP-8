#include <iostream>

#include "Chip8.h"

using namespace std;

Chip8 myChip8;

const char ROM[] = "./roms/IBM Logo.ch8";

int main(){

    myChip8.initialize();
    //myChip8.printMe();

    myChip8.loadGame(ROM);
    //myChip8.printMem(0x50, 650);

    for(int i = 0; i < 5; i++){
        myChip8.emulateCycle();

        if(myChip8.drawFlag){
            //updateGraphics();
        }
    }
    //myChip8.Grant();
    return 0;
}