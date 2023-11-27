#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "../include/cpu.h"

const int MEM_SIZE = 4096;
uint8_t *memory;

const int REG_COUNT = 16;
uint8_t *registers;

const int FONT_COUNT = 80;
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


const int CLOCK_RATE = 500;
double start_time_clock = 0; 

const uint8_t REFRESH_RATE = 60;
const uint8_t refresh_register = REFRESH_RATE;

uint16_t pc = 512; // Start of program memory

int refresh_display = 0;

void init_memory() {
    memory = (uint8_t *) calloc(MEM_SIZE, sizeof(uint8_t));
    if (!memory) {
        printf("Error initialising chip-8 memory. Exiting.");
        exit(EXIT_FAILURE);
    }
}

void init_registers() {
    registers = (uint8_t *) calloc(REG_COUNT, sizeof(uint8_t));
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

int cpu_tick() {
    double now = clock()/CLOCKS_PER_SEC;
    double elapsed = now - start_time_clock;

    if (!start_time_clock || elapsed >= (1/CLOCK_RATE)) {
        start_time_clock = now;
        return 1;
    } else {
        struct timespec delay;
        delay.tv_sec = 0;
        delay.tv_nsec = ((1/CLOCK_RATE) - elapsed) * 1000000000;

        while (nanosleep(&delay, &delay));
        return 0;
    }
}


void execute_next() {

}

void inc_pc() {
    pc += 2;
}
