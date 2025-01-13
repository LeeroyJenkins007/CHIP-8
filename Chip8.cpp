#include <iostream>
#include <fstream>
#include "Chip8.h"



Chip8::Chip8(){
    std::cout << "Creation of the the Chip 8 emulator" << std::endl;
}

void Chip8::initialize(){
    pc = 0x200;
    sp = 0;
    I = 0x200;

    //load font set into memory 0x50 - 0x9F
    for(uint8_t idx = 0; idx < 80; idx++){
        memory[idx+0x50] = fontset[idx];
    }
}

void Chip8::Grant(){
    std::cout << "Something Nice said by grant" << std::endl;
}

void Chip8::emulateCycle(){

    // Fetch Opcode
    opCode = (memory[pc] << 8) | memory[pc+1];
    std::cout << "OpCode: " << opCode << std::endl; 
    //increment to the next opcode since each opcode is 16 bits
    pc += 2;
    uint8_t nib[4] = {(opCode & 0xF000)>>4, opCode & 0x0F00, (opCode & 0x00F0)>>4, opCode & 0x000F};
    std::cout << "OpCode Nibs: " << std::hex << +nib[0] << ", " << +nib[1] << ", " << +nib[2] << ", " << +nib[3] << std::endl;

    // Decode Opcode
    switch(opCode){
        case 0x10:
            std::cout << "opcode 1\n";
            return;
        default:
            std::cout << "Default\n";
            return;
    }
    // Execute Opcode
}

void Chip8::loadGame(const char fname[]){
    std::cout << "Loading Game..." << std::endl;
    // testing the opcode
    //memory[0x200] = 0x00;
    //memory[0x201] = 0x33;
    uint8_t addr;
    char* memblock;
    std::streampos size;
    // open the rom files
    std::ifstream romFile (fname, std::ios::in|std::ios::binary|std::ios::ate);
    
    if(romFile.is_open()){
        //do something
        size = romFile.tellg();
        memblock = new char [size];
        // set the get position at the beginning of the file
        romFile.seekg(0, std::ios::beg);
        romFile.read(memblock, size);
        romFile.close();

        for(int i = 0; i < size; i++){
            memory[0x200 + i] = memblock[i];
            //std::cout << "memory[0x200 + " << i << "]: " << std::hex << std::setw(2) << +memory[0x200 + i] << std::endl;
            //printf("memory[0x200 + %02X]: %02X\n", i, memory[0x200 + i]);
        }
    }
    //std::cout << "memory[0x200 - 0x201]: " << +memory[0x200] << ", " << +memory[0x201] << std::endl;
}

const void Chip8::printMem(uint16_t start, uint16_t bytes){
    if(bytes > MEMORY_SIZE-start){
        std::cerr << "[ERROR] Trying to print more bytes than are in the memory!\n";
        return;
    }

    for(int i = 0; i < bytes; i++){
        printf("memory[%03X + %02X]: %02X\n", start, i, memory[start + i]);
    }
    
}