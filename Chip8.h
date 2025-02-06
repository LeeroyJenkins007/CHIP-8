#include <cstdint>
#ifndef CHIP8_H
#define CHIP8_H

const uint16_t MEMORY_SIZE = 4096;
const uint8_t GP_REG_SIZE = 16;
const uint8_t PXL_WIDTH = 64;
const uint8_t PXL_HEIGHT = 32;
const uint8_t STACK_SIZE = 16;

const uint16_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
     private:
        //program counter, index register
        uint16_t pc, I;
        //sound timer, delay timer
        uint8_t sound_t, delay_t;
        //general purpose registers V0-VF
        uint8_t gp_reg[GP_REG_SIZE];
        //stack implementation
        uint16_t stack[STACK_SIZE];
        //stack pointer implementation
        uint8_t sp;
        //RAM
        uint8_t memory[MEMORY_SIZE];
        //current opcode
        uint16_t opCode;
        //keypad
        uint8_t keypad[16];
    public:
        Chip8();
        void initialize();
        void emulateCycle();
        void loadGame(const char[]);
        void clearScreen();
        void Grant();
        const void printMem(uint16_t, uint16_t);

        //screen representation
        uint8_t gfx[PXL_HEIGHT * PXL_WIDTH];
        //flag if pixels were changed
        bool drawFlag;
};

#endif /*CHIP8_H*/