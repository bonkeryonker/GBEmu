#include <iostream> //printf
#include <memory> // shared_ptr
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"

int main()
{
	printf("Creating cartridge...");
	std::shared_ptr<Cartridge> cart_ptr = std::make_shared<Cartridge>();
	printf("OK\n");
	printf("Loading rom...");
	cart_ptr->loadROM("../../bin/testROMs/testSPAdd2.gb");
	printf("OK\n");
	printf("Creating RAM...");
	std::shared_ptr<Memory> ram_ptr = std::make_shared<Memory>(cart_ptr);
	printf("OK\n");
	printf("Creating CPU...");
	CPU c(ram_ptr);
	printf("OK\n");
	printf("Beginning execution...\n");
	while (!c.isHalted())
	{
		c.tick();
	}

	//ram_ptr->setItem(IE, 0x1a);
	// Finish up
	printf("\n");
	c.registers.printAsHex();
	printf("\n\n");
	printf("Halted: %s\n", c.isHalted() ? "TRUE" : "FALSE");
	ram_ptr->dumpMemoryToFile();
	//cart_ptr->dumpRomToFile();
}