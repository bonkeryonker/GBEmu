#include <iostream> //printf
#include <memory> // shared_ptr
#include <string>
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "Memory.h"
#include "Cartridge.h"
#include "SerialDebug.h"

int main()
{
	printf("Creating cartridge...");
	std::shared_ptr<Cartridge> cart_ptr = std::make_shared<Cartridge>();
	printf("OK\n");
	printf("Loading rom...");
	cart_ptr->loadROM("../../bin/testROMs/01-special.gb");
	printf("OK\n");
	printf("Creating RAM...");
	std::shared_ptr<Memory> ram_ptr = std::make_shared<Memory>(cart_ptr);
	printf("OK\n");
	printf("Creating CPU...");
	CPU c(ram_ptr);
	printf("OK\n");
	printf("Creating debug Serial Monitor...");
	SerialDebug sd(ram_ptr);
	printf("OK\n");
	printf("Beginning execution...\n");
	bool printRegisters = false;
	while (!c.isHalted())
	{
		if (c.registers.pc == 0xC36C)
		{
			system("cls");
			printf("PC: 0xC36C\n");
			printRegisters = true;
		}

		c.tick();
		if (printRegisters)
		{
			c.registers.printAsHex();
		}
	}
	printf("\n");

	//ram_ptr->setItem(IE, 0x1a);
	// Finish up
	printf("\n");
	c.registers.printAsHex();
	printf("\n\n");
	ram_ptr->dumpMemoryToFile();
	//cart_ptr->dumpRomToFile();
}