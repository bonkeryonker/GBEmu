#include "Gameboy.h"

Gameboy::Gameboy(std::shared_ptr<Window> drawWindow)
{
	this->cart = std::make_shared<Cartridge>();
	this->ram = std::make_shared<Memory>(this->cart);
	this->cpu = std::make_shared<CPU>(this->ram);
	this->ppu = std::make_shared<PPU::PPU>(this->ram, drawWindow);
	GB_WARN("Gameboy initialized");
}