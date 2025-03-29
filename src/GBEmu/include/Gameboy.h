#ifndef GB_H
#define GB_H
#include <memory>
#include <string>
#include "Globals.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"

class Gameboy
{
public:
	Gameboy();
	bool insertCartridge(std::string cartPath);
	void powerOn();
private:
	// Gameboy HW components
	std::shared_ptr<Cartridge> cart_ptr;
	std::shared_ptr<Memory> ram_ptr;
	std::shared_ptr<CPU> cpu_ptr;

	bool isPowered;
};
#endif