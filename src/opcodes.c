#include <stdint.h>

/*
    Clear screen, turning all pixels off to 0.
*/
void op_00E0() {

}

/*
    Jump pc to memory location. Do not increment the PC afterwards.
    @param nnn      Memory address to jump to 
*/
void op_1NNN(uint16_t nnn) {

}

/*
    Set register VX to value nn
    @param x        Register number
    @param nn       Value to set
*/
void op_6XNN(uint8_t x, uint8_t nn) {

}

/*
    Add value nn to register VX. Does not affect the carry flag VF if it overflows.
    @param x        Register number
    @param nn       Value to add     
*/
void op_7XNN(uint8_t x, uint8_t nn) {

}

/*
    Set index register I to value nnn
    @param nnn       Value to set
*/
void op_ANNN(uint16_t nnn) {

}

/*
    Draws the current state of the screen. It will draw an N pixels tall sprite 
    from the memory location that the I index register is holding to the screen, 
    at the horizontal X coordinate in VX and the Y coordinate in VY. 
    
    All the pixels that are “on” in the sprite will flip the pixels on the screen 
    that it is drawn to (from left to right, from most to least significant bit). 
    If any pixels on the screen were turned “off” by this, the VF flag register 
    is set to 1. Otherwise, it’s set to 0.
    @param x        horizontal coordinate
    @param y        vertical coordinate
    @param n        height of sprite to draw
*/
void op_DXYN(uint8_t x, uint8_t y, uint8_t n) {

}