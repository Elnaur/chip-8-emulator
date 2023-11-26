#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

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


typedef struct stack_entry Stack_entry;
struct stack_entry {
    uint16_t value;
    Stack_entry *next;
};

int stack_size = 0;
Stack_entry *stack;
void push(uint16_t value);
uint16_t pop();

const uint8_t SOUND_TIMER = 60;
uint8_t sound_timer = SOUND_TIMER;
double start_time_sound; // Set when sound timer started

const uint8_t DELAY_TIMER = 60;
uint8_t delay_timer = DELAY_TIMER;
double start_time_delay; // Set when delay timer started

const uint8_t CLOCK_RATE = 500;
double start_time_clock = 0; 

const uint8_t REFRESH_RATE = 60;
const uint8_t refresh_register = REFRESH_RATE;

uint16_t pc = 512; // Start of program memory

int display_update = 0;

void init_memory();
void init_registers();
void load_font();
int cpu_tick();
void inc_pc();
void execute_next();

int main(int argc, char *argv[]) {
    init_memory();
    init_registers();

    load_font();

    while (1)
    {
        if (sound_timer) {
            dec_sound_timer();
        } 

        if (delay_timer) {
            dec_delay_timer();
        }

        if (cpu_tick()) {
            execute_next();
        }
    }
    
    return EXIT_SUCCESS;
}

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

void push(uint16_t value) {
    Stack_entry *entry = (Stack_entry *) calloc(1, sizeof(Stack_entry));
    if (!entry) {
        printf("Error initialising chip-8 stack entry. Exiting.");
        exit(EXIT_FAILURE);           
    }

    entry->value = value;

    if (stack_size == 0) {
        stack = entry;
        stack->next = NULL;
    } else {
        entry->next = stack;
        stack = entry;
    }

    stack_size++;
}

uint16_t pop() {
    uint16_t value;
    Stack_entry *temp_entry;

    value = stack->value;

    temp_entry = stack->next;
    free(stack);
    stack = temp_entry;

    stack_size--;   
    return value; 
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

int dec_sound_timer() {
    double now = clock()/CLOCKS_PER_SEC;
    double elapsed = now - start_time_sound;

    if (elapsed >= (1/SOUND_TIMER)) {
        start_time_sound = now;
        sound_timer--;

        beep();
    }
}

int dec_delay_timer() {
    double now = clock()/CLOCKS_PER_SEC;
    double elapsed = now - start_time_delay;

    if (elapsed >= (1/DELAY_TIMER)) {
        start_time_delay = now;
        delay_timer--;
    }
}

void beep() {
    printf("\a");
}

void execute_next() {

}

void inc_pc() {
    pc += 2;
}