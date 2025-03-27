#ifndef GLOBALS_H
#define GLOBALS_H
#include <cstdint>
#include "Log.h"

typedef uint8_t u8;
typedef uint16_t u16;
static constexpr u16 MAX_CARTSIZE = 0x8000;
static constexpr u16 HEADER_CHECKSUM_ADDRESS = 0x014D;
static constexpr u16 GLOBAL_CHECKSUM_ADDRESS = 0x014E; // Big endian, 0x014E is high byte
static constexpr u16 RAM_SIZE = (0xFFFF - MAX_CARTSIZE) + 0x01;
static constexpr int LCD_WIDTH = 160;
static constexpr int LCD_HEIGHT = 144;
#endif