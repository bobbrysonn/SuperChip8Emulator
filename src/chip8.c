// File: chip8.c
//
// Purpose: Emulate super chip 8
//
// Author: Bob Moriasi
// Date: May 16, 2025
//
// Copyright: (C) 2025

#include "chip8.h"
#include <corecrt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void chip8_clear_graphics(chip8_t *chip8)
{
    memset(chip8->gfx, 0, sizeof(chip8->gfx));

    chip8->draw_flag = true;
}

void chip8_cycle(chip8_t *chip8)
{
    chip8->opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];

    const uint8_t x = (chip8->opcode & 0x0F00) >> 8;
    const uint8_t y = (chip8->opcode & 0x00F0) >> 4;
    const uint8_t kk = chip8->opcode & 0x00FF;
    const uint8_t n = chip8->opcode & 0x000F;
    const uint16_t nnn = chip8->opcode & 0x0FFF;

    switch (chip8->opcode & 0xF000)
    {
        default: {
            fprintf(stderr, "Unknown opcode: 0x%04X\n", chip8->opcode);
        }
    }
}

void chip8_increment_pc(chip8_t *chip8)
{
    chip8->pc += 2;
}

void chip8_init(chip8_t *chip8)
{
    srand(time(nullptr));
    memset(chip8, 0, sizeof(*chip8));

    chip8->pc = 0x200;

    chip8_clear_graphics(chip8);
    chip8_load_fonts(chip8, chip8_font_set);
}

bool chip8_load_fonts(chip8_t *chip8, uint8_t font_set[FONT_SET_SIZE])
{
    for (int i = 0; i < FONT_SET_SIZE; i++)
    {
        chip8->memory[FONT_START_ADDRESS + i] = font_set[i];
    }
    return true;
}

bool chip8_load_rom(chip8_t *chip8, const char *filename)
{
    FILE *fp;
    errno_t err;

    if ((err = fopen_s(&fp, filename, "rb")) != 0)
    {
        fprintf(stderr, "Cannot open file '%s': %s\n", filename, strerror(err));

        return false;
    }

    int i = 0;
    uint8_t byte;
    while (fread(&byte, 1, 1, fp) == 1)
    {
        if (0x200 + i >= CHIP8_MEM_SIZE)
        {
            fprintf(stderr, "Rom is too large for memory\n");
            fclose(fp);

            return false;
        }

        chip8->memory[0x200 + i++] = byte;
    }

    fclose(fp);

    return true;
}

uint8_t chip8_font_set[FONT_SET_SIZE] = {
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