#ifndef RAM_H
#define RAM_H
#include <cstdint>
#include <cstring> // For memset() with Ubuntu c++ compiler
#include <stdio.h>
#include <fstream>
#include <memory>
#include "Cartridge.h"
#include "Globals.h"

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

class Memory
{
public:
	static inline bool isRomAddress(u16 address) { return address < VRAM; }

	// Allocates RAM_SIZE bytes on the heap, and sets them all to 0x00
	Memory(std::shared_ptr<Cartridge>& cart_ptr);

	// Delete[]'s the ram buffer
	~Memory();

	// Returns the byte at the specified address in memory
	u8 getItem(u16 address);

	// Sets the byte at the specified address in memory to the passed value.
	// RETURNS: true if write was successful (Address not in cartridge ROM).
	bool setItem(u16 address, u8 value);

	// Outputs the full contents of RAM to a binary file
	bool dumpMemoryToFile(const std::string& filename="../../bin/memdumps/mem_dump.bin", bool dumpCartridge=true);
	inline bool dumpMemoryToFile(bool dumpCartridge) { return this->dumpMemoryToFile("../../bin/memdumps/mem_dump.bin", dumpCartridge); }

	// Uses writeStringsASCII to write ascii text at the beginning of all memory maps
	// specified in MemoryMap.
	void setDebugValues();

private:
	u8* ramBuf;
	std::shared_ptr<Cartridge> cart_ptr;

	// Offset the passed address to point to the correct value in ram buffer.
	// (Ex: 0x8000 returns 0x0000)
	u16 normalizeAddress(u16 address);

};
#endif
