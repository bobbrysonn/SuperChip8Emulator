// File: main.c
//
// Purpose: Emulate super chip 8
//
// Author: Bob Moriasi
// Date: May 16, 2025
//
// Copyright: (C) 2025

#include "chip8.h"
#include <stdio.h>
#include <stdlib.h>

void de_init();
bool init(const char *filename);

chip8_t *cpu = nullptr;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "No Rom file name specified\n");
        fprintf(stderr, "Usage: %s <rom file>\n", argv[0]);
        return 1;
    }

    if (!init(argv[1]))
    {
        fprintf(stderr, "Failed to initialize\n");
        return 1;
    }

    de_init();
}

void de_init()
{
    free(cpu);
}

bool init(const char *filename)
{
    cpu = malloc(sizeof(chip8_t));
    if (!cpu)
    {
        fprintf(stderr, "Failed to allocate memory for cpu\n");
        return false;
    }

    chip8_init(cpu);
    if (!(chip8_load_rom(cpu, filename)))
    {
        fprintf(stderr, "Could not load rom\n");
        return false;
    }

    return true;
}