#include <iostream> //printf
#include <memory> // shared_ptr
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"

int main()
{
	std::shared_ptr<Cartridge> cart_ptr = std::make_shared<Cartridge>();
	cart_ptr->loadROM("../../bin/testROMs/nopStop.gb");
	std::shared_ptr<Memory> ram_ptr = std::make_shared<Memory>(cart_ptr);
	CPU c(ram_ptr);

	ram_ptr->setItem(IE, 0x1a);
	// Finish up
	c.registers.printAsHex();
	printf("Halted: %s\n", c.isHalted() ? "TRUE" : "FALSE");
	ram_ptr->dumpMemoryToFile();
	//cart_ptr->dumpRomToFile();
}