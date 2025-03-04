#include <iostream> //printf
#include <memory> // shared_ptr
#include "Clock.h"
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"
#include "Cartridge.h"

bool loadTestCart(std::shared_ptr<RAM> ram_ptr);

int main()
{
	std::shared_ptr<RAM> ram_ptr = std::make_shared<RAM>();
	CPU c(ram_ptr);
	
	if (!loadTestCart(ram_ptr))
		return 1;

	// Begin ROM execution
	while (!c.isHalted())
	{
		Clock::tick(c);
	}

	// Finish up
	c.registers.printAsHex();
	printf("Halted: %s\n", c.isHalted() ? "TRUE" : "FALSE");
	ram_ptr->dumpMemoryToFile();
}

bool loadTestCart(std::shared_ptr<RAM> ram_ptr)
{
	// Load ROM
	Cartridge::loadFromFile(ram_ptr, "../../bin/testROMs/testCPL.gb");
	if (!Cartridge::validateChecksums(ram_ptr))
	{
		printf("Invalid ROM checksum(s). Overriding...\n");
		printf("Would you like to override? (y/N)\n");
		char userin;
		std::cin >> userin;
		if (userin != 'y' && userin != 'Y')
		{
			printf("Aborting...\n");
			return false;
		}
		printf("Overriding...\n");
		Cartridge::overrideChecksums(ram_ptr);
	}
	printf("ROM checksums good!\n");
	return true;
}