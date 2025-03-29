#include "Gameboy.h"

Gameboy::Gameboy()
{
	this->cart_ptr = std::make_shared<Cartridge>();
	this->ram_ptr = std::make_shared<Memory>(this->cart_ptr);
	this->cpu_ptr = std::make_shared<CPU>(this->ram_ptr);
	this->isPowered = false;
}

bool Gameboy::insertCartridge(std::string cartPath)
{
	return this->cart_ptr->loadROM(cartPath);
}

void Gameboy::powerOn()
{
	this->isPowered = true;
}