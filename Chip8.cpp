#include <iostream>
#include <fstream>
#include "Chip8.h"



Chip8::Chip8(){
    std::cout << "Creation of the the Chip 8 emulator" << std::endl;
}

void Chip8::initialize(){
    pc = 0x200;
    sp = 0;
    I = 0;

    //load font set into memory 0x50 - 0x9F
    for(uint8_t idx = 0; idx < 80; idx++){
        memory[idx+0x50] = fontset[idx];
    }

}

void Chip8::clearScreen(){
    for(int i = 0; i < PXL_HEIGHT * PXL_WIDTH; i++){
        gfx[i] = 0;
    }

}


void Chip8::Grant(){
    std::cout << "Something Nice said by grant" << std::endl;
}

void Chip8::emulateCycle(){

    // Fetch Opcode
    opCode = (memory[pc] << 8) | memory[pc+1];
    //std::cout << "OpCode: " << opCode << std::endl; 
    //increment to the next opcode since each opcode is 16 bits
    //std::cout << std::hex << "0x" << pc << "\t 0x" << opCode << "\n";
    pc += 2;
    //should put this into a struct
    uint8_t nib[4] = {(uint8_t)((opCode & 0xF000)>>12), (uint8_t)((opCode & 0x0F00)>>8), (uint8_t)((opCode & 0x00F0)>>4), (uint8_t)(opCode & 0x000F)};
    //std::cout << "OpCode Nibs: " << std::hex << +nib[0] << ", " << +nib[1] << ", " << +nib[2] << ", " << +nib[3] << std::endl;

    // Decode Opcode
    switch(nib[0]){
        case 0x0:
            //std::cout << "opcode 0\n";
            //std::cout << "back sequence: " << (nib[2]<<4 | nib[3]) << std::endl;
            switch(nib[2]<<4 | nib[3]){
                // cls
                case 0xE0:
                    //std::cout << "CLS\n";
                    clearScreen();
                    drawFlag = true;
                    return;
                default:
                    return;
            }
            return;
        case 0x1:{
            //std::cout << "opcode 1\n";
            uint16_t jmpAddr = (nib[1]<<8 | nib[2]<<4 | nib[3]);
            pc = jmpAddr;
            //std::cout << "JUMP to " << std::hex << jmpAddr << std::endl;
            return;
            }
        case 0x2:
            std::cout << "opcode 2\n";
            return;
        case 0x3:
            std::cout << "opcode 3\n";
            return;
        case 0x4:
            std::cout << "opcode 4\n";
            return;
        case 0x5:
            std::cout << "opcode 5\n";
            return;
        case 0x6:
            // mov VX, RR
            //std::cout << "opcode 6\n";
            gp_reg[nib[1]] = (nib[2]<<4 | nib[3]);
            return;
        case 0x7:
            //add VX, RR
            //std::cout << "opcode 7\n";
            gp_reg[nib[1]] += (nib[2]<<4 | nib[3]);
            return;
        case 0x8:
            std::cout << "opcode 8\n";
            return;
        case 0x9:
            std::cout << "opcode 9\n";
            return;
        case 0xA:
            // mvi NNN
            //std::cout << "opcode A\n";
            I = (nib[1]<<8|nib[2]<<4|nib[3]);
            //std::cout << "New I: " << std::hex << I << "\n";
            return;
        case 0xB:
            std::cout << "opcode B\n";
            return;
        case 0xC:
            std::cout << "opcode C\n";
            return;
        case 0xD:{
            //sprite vx,vy,n
            //std::cout << "opcode D\n";
            //std::cout << "Draw to Screen: \n";
            uint8_t xcoord = gp_reg[nib[1]] % PXL_WIDTH;
            uint8_t ycoord = gp_reg[nib[2]] % PXL_HEIGHT;

           //std::cout << "\t x: " << +xcoord << "\t xraw: " << +gp_reg[nib[1]] << " @ " << +nib[1] << "\n";
           //std::cout << "\t y: " << +ycoord << "\t yraw: " << +gp_reg[nib[2]] << " @ " << +nib[2] << "\n";
           //std::cout << "N: " << +nib[3] << "\n";
           gp_reg[0xF] = 0;
           for(uint8_t row = 0; row < nib[3]; row++){
                uint8_t sprite = memory[I + row];
                //std::cout << "Row: " << +row << "\n";
                
                for(uint8_t col = 0; col < 8; col++){
                    uint16_t pxLoc = xcoord + col + ((ycoord + row )*PXL_WIDTH);
                    //std::cout << "Col: " << +col << "\n";
                    //std::cout << +pxLoc << "\n";
                    uint8_t pixel = gfx[pxLoc];

                    //if the sprite pixel is 'on'
                    if(sprite & (0x1 << (7 - col))){
                        //pixel is 'on' AND sprite pixel is 'on'
                        if(pixel){
                            //gfx[pxLoc] = 0;
                            gp_reg[0xF] = 1;
                        }else{
                            gfx[pxLoc] ^= 1;
                        }

                    }

                    if(xcoord + col == PXL_WIDTH-1)
                        break;

                } //for columns
                if(ycoord + row == PXL_HEIGHT-1)
                    break;
           } //for rows

            drawFlag = true;
            return;
            }
        case 0xE:
            std::cout << "opcode E\n";
            return;
        case 0xF:
            std::cout << "opcode F\n";
            return;
        default:
            std::cout << "Not a valid opcode: " << std::hex << opCode << std::endl;
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