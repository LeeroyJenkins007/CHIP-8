#include <iostream>
#include "Chip8.h"



Chip8::Chip8(int initVal) : test(initVal){
    std::cout << "Creation of the the Chip 8 emulator\n";
    std::cout << "Init: " << test << std::endl;
}

const void Chip8::printMe(){
    std::cout << "This is the chip8 class\n";
}