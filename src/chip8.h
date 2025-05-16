// File: chip8.h
//
// Purpose: Emulate super chip 8 
//
// Author: Bob Moriasi
// Date: May 16, 2025
//
// Copyright: (C) 2025

#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define CHIP8_MEM_SIZE 4096
#define CHIP8_NUM_KEYS 16
#define CHIP8_REG_SIZE 16
#define CHIP8_SCREEN_HEIGHT 32
#define CHIP8_SCREEN_WIDTH 64
#define CHIP8_STACK_SIZE 16
#define FONT_SET_SIZE 80
#define FONT_START_ADDRESS 0x050

extern uint8_t chip8_font_set[FONT_SET_SIZE];

typedef struct
{
    bool draw_flag;
    uint8_t gfx[CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT];
    uint8_t key[CHIP8_NUM_KEYS];
    uint8_t memory[CHIP8_MEM_SIZE];
    uint8_t timer_delay;
    uint8_t timer_sound;
    uint8_t V[CHIP8_REG_SIZE];
    uint16_t I;
    uint16_t opcode;
    uint16_t pc;
    uint16_t sp;
    uint16_t stack[CHIP8_STACK_SIZE];
} chip8_t;

/**
 * Load the font set into chip8 ram between position 0x050 moving foward
 */
bool chip8_load_fonts(chip8_t *chip8, uint8_t font_set[FONT_SET_SIZE]);

/**
 * Load a game from a file
 */
bool chip8_load_rom(chip8_t *chip8, const char *filename);

/**
 * Zero out gfx
 */
void chip8_clear_graphics(chip8_t *chip8);

/**
 * Cycle through and execute opcodes
 */
void chip8_cycle(chip8_t *chip8);

/**
 * Move ahead two steps
 */
void chip8_increment_pc(chip8_t *chip8);

/**
 * Initialize the chip8 cpu
 */
void chip8_init(chip8_t *chip8);

#endif // CHIP_8H