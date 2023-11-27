#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "../include/timers.h"

const uint8_t SOUND_TIMER = 60;
double start_time_sound; // Set when sound timer started

const uint8_t DELAY_TIMER = 60;
double start_time_delay; // Set when delay timer started

void beep();

void start_sound_timer() {
    start_time_sound = clock()/CLOCKS_PER_SEC;
    sound_timer = SOUND_TIMER;
}

void start_delay_timer() {
    start_time_delay = clock()/CLOCKS_PER_SEC;
    sound_timer = DELAY_TIMER;
}

void dec_sound_timer() {
    double now = clock()/CLOCKS_PER_SEC;
    double elapsed = now - start_time_sound;

    if (elapsed >= (1/SOUND_TIMER)) {
        start_time_sound = now;
        sound_timer--;

        beep();
    }
}

void dec_delay_timer() {
    double now = clock()/CLOCKS_PER_SEC;
    double elapsed = now - start_time_delay;

    if (elapsed >= (1/DELAY_TIMER)) {
        start_time_delay = now;
        delay_timer--;
    }
}

void beep() {
    printf("\a");
    fflush(stdout);
}
