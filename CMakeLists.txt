cmake_minimum_required(VERSION 3.20)

project(
    SuperChip8Emulator
    VERSION 1.0
    DESCRIPTION "A Super Chip8 Emulator"
    LANGUAGES C
)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(
    SOURCES
    src/chip8.h
    src/chip8.c
    src/main.c
)

find_package(SDL3 CONFIG REQUIRED)

add_executable(SuperChip8Emulator ${SOURCES})

target_link_libraries(SuperChip8Emulator PRIVATE SDL3::SDL3)