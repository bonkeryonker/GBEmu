#include "RAM.h"

void RAM::init()
{
	for (auto i = 0; i < 0xFFFF; i++)
		RAM::ram[i] = 0x00;
}

uint8_t RAM::getItem(uint16_t address)
{
	//TODO: redirect addresses that point to cartridge to the cartridge memory
	return RAM::ram[address];
}

bool RAM::setItem(uint16_t address, uint8_t value)
{
	// Return false if the passed address falls into cartridge ROM
	if (address < RAM::MemoryMap::VRAM)
	{
#ifdef _DEBUG
		printf("Address %04X is Cartridge ROM.\n", address);
#endif
		return false;
	}
	else
	{
		// Return false if the passed address falls into ranges forbidden by Nintendo
		if ((address >= RAM::MemoryMap::ECHO) && (address < RAM::MemoryMap::OAM) ||
			(address >= RAM::MemoryMap::FORBIDDEN) && (address < RAM::MemoryMap::IO))
		{
#ifdef _DEBUG
			printf("Address %04X is forbidden by Nintendo.\n", address);
#endif
			return false;
		}
		// Redirect addresses stored on Cartridge RAM to the relevant accessor(s) and return true
		else if ((address >= RAM::MemoryMap::EXTERNALRAM) && (address < RAM::MemoryMap::WRAM0))
		{
			// TODO: redirect address to external cartridge RAM
			return true;
		}
		else
		{
			RAM::ram[address] = value;
			return true;
		}
	}
}

void RAM::setDebugValues()
{
	setItem(MemoryMap::VRAM, 0xde);
	setItem(MemoryMap::VRAM + 1, 0xad);
	setItem(MemoryMap::VRAM + 2, 0xbe);
	setItem(MemoryMap::VRAM + 3, 0xef);
}

bool RAM::dumpMemoryToFile(const std::string& filename)
{
	std::ofstream outFile(filename, std::ios::binary);
	if (!outFile)
	{
		printf("Unable to open file for writing\n");
		return false;
	}
	outFile.write(reinterpret_cast<const char*>(RAM::ram), RAM_SIZE + 1);
	outFile.close();
	return true;
}