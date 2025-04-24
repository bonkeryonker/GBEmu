#ifndef GFX_H
#define GFX_H
#include "Globals.h"
#include <tuple> // std::pair

static constexpr int TILE_SIZE_PX = 8;
static constexpr int TILE_SIZE_BYTE = 16;

// The amount of tiles in a tilemap
static constexpr int TILEMAP_TILECOUNT = 32;
// Size of a tilemap in bytes (tilemaps are 32x32 maps of one-byte indices to 2bpp-tiledata)
static constexpr int TILEMAP_SIZE_BYTE = TILEMAP_TILECOUNT * TILEMAP_TILECOUNT;

struct Color_RGBA {
    uint32_t value;

    constexpr Color_RGBA(uint32_t val = 0) : value(val) {}
    constexpr Color_RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : value((a << 24) | (b << 16) | (g << 8) | r) {
    }

    constexpr uint8_t r() const { return value & 0xFF; }
    constexpr uint8_t g() const { return (value >> 8) & 0xFF; }
    constexpr uint8_t b() const { return (value >> 16) & 0xFF; }
    constexpr uint8_t a() const { return (value >> 24) & 0xFF; }

    constexpr void set_r(uint8_t v) { value = (value & 0xFFFFFF00) | v; }
    constexpr void set_g(uint8_t v) { value = (value & 0xFFFF00FF) | (v << 8); }
    constexpr void set_b(uint8_t v) { value = (value & 0xFF00FFFF) | (v << 16); }
    constexpr void set_a(uint8_t v) { value = (value & 0x00FFFFFF) | (v << 24); }

    constexpr operator uint32_t() const { return value; }
};

typedef struct DMGPaletteColors_RGBA
{
    static constexpr Color_RGBA WHITE = Color_RGBA(0xE0, 0xF8, 0xD0, 0xFF);
    static constexpr Color_RGBA LIGHT_GRAY = Color_RGBA(0x88, 0xC0, 0x70, 0xFF);
    static constexpr Color_RGBA DARK_GRAY = Color_RGBA(0x34, 0x68, 0x56, 0xFF);
    static constexpr Color_RGBA BLACK = Color_RGBA(0x08, 0x18, 0x20, 0xFF);

    static constexpr Color_RGBA getColor(bool high, bool low)
    {
        if (high && low)
            return BLACK;
        else if (high && !low)
            return DARK_GRAY;
        else if (!high && low)
            return LIGHT_GRAY;
        else
            return WHITE;
    }

    static const char* toString(Color_RGBA color)
    {
        switch (color)
        {
        case BLACK:
            return "BLACK";
        case DARK_GRAY:
            return "DARK_GRAY";
        case LIGHT_GRAY:
            return "LIGHT_GRAY";
        case WHITE:
            return "WHITE";
        default:
            return "UNKNOWN";
        }
    }
}DMGColors;

typedef struct GB_Tile_Row
{
    union
    {
        struct
        {
            u8 low;
            u8 high;
        };
        u16 data;
    };
    constexpr GB_Tile_Row() : data(0) {}
    constexpr GB_Tile_Row(u16 data) : data(data) {}
    constexpr GB_Tile_Row(u8 low, u8 high) : low(low), high(high) {}
}TileRow;

typedef struct Gameboy_Tile
{
    union
    {
        struct
        {
            TileRow row0;
            TileRow row1;
            TileRow row2;
            TileRow row3;
            TileRow row4;
            TileRow row5;
            TileRow row6;
            TileRow row7;
        };
        TileRow rows[8]; // Row-wise access
        u8 bytes[16]; // Byte-wise access
    };

    Gameboy_Tile() : rows{} {}

    std::pair<uint64_t, uint64_t> toHex() const
    {
        uint64_t low = 0;
        uint64_t high = 0;

        for (int i = 0; i < 8; i++)
            low |= (uint64_t)(bytes[i]) << (8 * (7 - i)); // byte[0] ends up in MSB of low

        for (int i = 8; i < 16; i++)
            high |= (uint64_t)(bytes[i]) << (8 * (15 - i)); // byte[8] in MSB of high

        return { high, low };
    }
}Tile;
#endif