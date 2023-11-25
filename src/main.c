#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

const int MEM_SIZE = 4096;
uint8_t *memory;

const int REG_COUNT = 16;
uint8_t registers;

FONT_COUNT = 80;
const uint8_t fontset[FONT_COUNT] = {   0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
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

void init_memory();
void init_registers();
void load_font();

int main(int argc, char *argv[]) {
    init_memory();
    init_registers();

    load_font();

    return EXIT_SUCCESS;
}

void init_memory() {
    memory = calloc(MEM_SIZE, sizeof(uint8_t));
    if (!memory) {
        printf("Error initialising chip-8 memory. Exiting.");
        exit(EXIT_FAILURE);
    }
}

void init_registers() {
    registers = calloc(REG_COUNT, sizeof(uint8_t));
    if (!registers) {
        printf("Error initialising chip-8 registers. Exiting.");
        exit(EXIT_FAILURE);
    }
}

void load_font() {
    int i;
    for (i = 0; i < FONT_COUNT; i++) {
        memory[i] = fontset[i];
    }
}