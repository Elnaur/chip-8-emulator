#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include "../include/cpu.h"
#include "../include/timers.h"

typedef struct stack_entry Stack_entry;
struct stack_entry {
    uint16_t value;
    Stack_entry *next;
};

int stack_size = 0;
Stack_entry *stack;
void push(uint16_t value);
uint16_t pop();

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

        inc_pc();
    }
    
    return EXIT_SUCCESS;
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

