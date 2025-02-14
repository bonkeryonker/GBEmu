#ifndef RAM_H
#define RAM_H
#include <cstdint>
#include <stdio.h>
#include <fstream>

#define RAM_SIZE 0xFFFF
namespace RAM
{
	/*
	* Enum containing common memory offsets.
	*/
	enum MemoryMap
	{
		//Cartridge, usually fixed bank.
		ROMBANK00 = 0x0000,
		
		//Cartridge, Switchable bank
		ROMBANK01_N = 0x4000,
		
		//Video RAM
		VRAM = 0x8000,

		//Cartridge, Potentially switchable bank
		EXTERNALRAM = 0xA000,

		//Working RAM
		WRAM0 = 0xC000,
		WRAM1 = 0xD000,
		
		//Prohibited by Nintendo
		ECHO = 0xE000,
		
		//Object Attribute Memory
		OAM = 0xFE00,

		//Area forbidden by Nintendo
		FORBIDDEN = 0xFEA0,

		//Input/Output Registers
		IO = 0xFF00,

		//High RAM
		HRAM = 0xFF80,

		//Interrupt Enable Register (one byte in length)
		IE = 0xFFFF
	};

	static uint8_t ram[RAM_SIZE];

	// Initializes all RAM values to 0x00
	void init();

	// Returns the byte at the specified address in memory
	uint8_t getItem(uint16_t address);

	// Writes an ascii string starting at the specified address in memory
	bool writeStringASCII(uint16_t startAddress, std::string value);

	void setDebugValues();
	bool dumpMemoryToFile(const std::string& filename);

	// Sets the byte at the specified address in memory to the passed value.
	// Returns: True if successful
	bool setItem(uint16_t address, uint8_t value);
}
#endif
