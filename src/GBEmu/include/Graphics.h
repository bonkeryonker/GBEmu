#ifndef GFX_H
#define GFX_H
#include "Globals.h"

static constexpr int TILE_SIZE_PX = 8;
static constexpr int TILEMAP_SIZE = 32;

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

struct DMGPaletteColors_RGBA
{
    static constexpr Color_RGBA WHITE = Color_RGBA(0xE0, 0xF8, 0xD0, 0xFF);
    static constexpr Color_RGBA LIGHT_GRAY = Color_RGBA(0x88, 0xC0, 0x70, 0xFF);
    static constexpr Color_RGBA DARK_GRAY = Color_RGBA(0x34, 0x68, 0x56, 0xFF);
    static constexpr Color_RGBA BLACK = Color_RGBA(0x08, 0x18, 0x20, 0xFF);
};
#endif