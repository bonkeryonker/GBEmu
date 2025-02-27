#ifndef RAM_H
#define RAM_H
#include <cstdint>
#include <cstring> // For memset() with Ubuntu c++ compiler
#include <stdio.h>
#include <fstream>
#include <memory>
#include "Globals.h"

#define RAM_SIZE 0xFFFF

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

class RAM
{
public:

	// Allocates RAM_SIZE bytes on the heap, and sets them all to 0x00
	RAM();

	// Delete[]'s the ram buffer
	~RAM();

	// Returns the byte at the specified address in memory
	u8 getItem(u16 address);

	// Sets the byte at the specified address in memory to the passed value.
	void setItem(u16 address, u8 value);

	// Writes an ascii string starting at the specified address in memory
	// Returns: False if the length of the string would overwrite the buffer
	bool writeStringASCII(u16 startAddress, std::string value);

	// Outputs the full contents of RAM to a binary file
	bool dumpMemoryToFile(const std::string& filename="ram_dump.bin");

	// Uses writeStringsASCII to write ascii text at the beginning of all memory maps
	// specified in MemoryMap.
	void setDebugValues();

private:
	u8* ramBuf;

};
#endif
