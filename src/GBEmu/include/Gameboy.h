#ifndef GB_H
#define GB_H
#include <memory> // shared_ptr
#include "Log.h"
#include "Memory.h"
#include "Cartridge.h"
#include "CPU.h"
#include "PPU.h"

class Gameboy
{
public:
	Gameboy();
public:
	std::shared_ptr<Cartridge> cart;
	std::shared_ptr<Memory> ram;
	std::shared_ptr<CPU> cpu;
	std::shared_ptr<PPU::PPU> ppu;
};
#endif

